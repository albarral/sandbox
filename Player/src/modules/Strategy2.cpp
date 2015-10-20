/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Strategy2.h"
#include "PlayerActions.h"
#include "data/GameBoard.h"
#include "learn/GameDistance.h"

namespace sam
{    
log4cxx::LoggerPtr Strategy2::logger(log4cxx::Logger::getLogger("sam.player"));

Strategy2::Strategy2() 
{
    benabled = false;
}

void Strategy2::init(GameTask& oGameTask)
{
    pGameTask = &oGameTask;
    benabled = true;
    oLearn.setGamma(0.8);

    LOG4CXX_INFO(logger, "Strategy2 functionality initialized");      
};

bool Strategy2::playRandom(cv::Mat& matrix, int myMark)
{
    // Search for the empty cells and choose one of them randomly
    std::vector<std::pair<int, int>> listEmptyCells;
    cv::Mat matRow;
    
    // get list of empty cells 
    for (int i=0; i<matrix.rows; i++)
    {
        matRow = matrix.row(i);                
        for (int j=0; j<matRow.cols; j++)
        {
            if (matRow.at<int>(j) == GameBoard::EMPTY_MARK)
                listEmptyCells.push_back(std::make_pair(i,j));
        }
    }

    if (listEmptyCells.size() > 0)
    {
        // randomly select an empty cell
        int randNum = rand() % listEmptyCells.size();
        std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
        // and set it as best move
        bestMove[0] = selectedCell.first;   
        bestMove[1] = selectedCell.second; 
        return true;
    }
    else
        return false;
}

// Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
void Strategy2::playSmart(cv::Mat& matrix, int myMark)
{    
    Line oLine;
    oLine.setMatrix(matrix);

    LOG4CXX_INFO(logger, "Strategy2: play smart ...");   

    // zero reward before the analysis
    bestReward = 0.0;

    // check rows
    LOG4CXX_INFO(logger, "CHECK ROWS");   
    for (int i=0; i<matrix.rows; i++)
    {
        // analyse row & check proper moves in it
        oLine.checkRow(i, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eLINE_ROW, i, oLine);
    }    

    // check columns
    LOG4CXX_INFO(logger, "CHECK COLUMNS");   
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check proper moves in it
        oLine.checkColumn(j, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eLINE_COL, j, oLine);
    }    
    
    // check diagonals
    LOG4CXX_INFO(logger, "CHECK DIAGONALS");   
    // analyse first diagonal & check proper moves in it
    int lineType = Line::eLINE_DIAG1;
    oLine.checkDiagonal(lineType, myMark, GameBoard::EMPTY_MARK);        
    checkBestMoveInLine(lineType, 0, oLine);

    // analyse second diagonal & check proper moves in it
    lineType = Line::eLINE_DIAG2;
    oLine.checkDiagonal(lineType, myMark, GameBoard::EMPTY_MARK);        
    checkBestMoveInLine(lineType, 0, oLine);
    
    LOG4CXX_INFO(logger, toStringBestMove());      
}


// checks if the given line holds the best move in the board 
void Strategy2::checkBestMoveInLine(int lineType, int linePosition, Line& oLine)
{
    float maxLineReward = 0.0;
    PlayerActions oPlayerActions;

    LOG4CXX_INFO(logger, "check line " << linePosition);   
    
    // analyzes the line to obtain its best transition
    Transition* pBestTransition = analyseLine(oLine);    
    
    // if line transition was found ...
    if (pBestTransition != 0)
    {
        maxLineReward = pBestTransition->getQ();
        LOG4CXX_INFO(logger, "max Q = " << maxLineReward);   
        
        // and it's the best transition till the moment
        if (maxLineReward > bestReward)
        {
            bestReward = maxLineReward;
                        
            // deduce the action that causes this transition
            GameState& state1 = pGameTask->getListGameStates().at(pBestTransition->getStateID());
            GameState& state2 = pGameTask->getListGameStates().at(pBestTransition->getNextState());                        
            // deduce it in the line's domain
            if (oPlayerActions.getActions4Transition(state1, state2) > 0)
            {
                int x, y;
                
                // then translate it to the board's domain
                switch (lineType)
                {
                    case Line::eLINE_ROW:
                        oPlayerActions.applyAction2Row(linePosition, x, y);
                        break;
                    case Line::eLINE_COL:
                        oPlayerActions.applyAction2Column(linePosition, x, y);
                        break;
                    case Line::eLINE_DIAG1:
                    case Line::eLINE_DIAG2:
                        oPlayerActions.applyAction2Diagonal(lineType, x, y);
                        break;                                                
                }
                        
                // store this best move till now
                bestMove[0] = y;   // y stores the row
                bestMove[1] = x;   // x stores the column
            }
        }
    }    
}


// (CORE OF THE SMART STRATEGY)
// Uses the learned knowledge about the task to obtain the best rewarded transition in this line
Transition* Strategy2::analyseLine(Line& oLine)
{
    GameState* pPresentGameState = 0;
    int* lineCells = oLine.getCells();
    
    // Find the game state that represents the configuration of the given line
    std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
    std::vector<sam::GameState>::iterator it_gameState = listGameStates.begin();
    std::vector<sam::GameState>::iterator it_end = listGameStates.end();
    while (it_gameState != it_end)
    {        
        int* gameStateCells = it_gameState->getCells();
        
        if (gameStateCells[0] == lineCells[0] && gameStateCells[1] == lineCells[1] && gameStateCells[2] == lineCells[2])
        {
            pPresentGameState = &(*it_gameState);
            break;
        }
        it_gameState++;
    }    
    
    LOG4CXX_INFO(logger, "present " << pPresentGameState->toString());   
    
    // From the present state, find the best possible transition
    if (pPresentGameState->getListTransitions().size() > 0)
    {
        // the best  transition is the one with maximum Q value 
        return (findBestTransition(pPresentGameState->getListTransitions()));   
    }    
    // if present state allows no transition
    else
        return 0;
}


Transition* Strategy2::findBestTransition(std::vector<sam::Transition>& listTransitions)
{
    sam::Transition* winnerTemporal = 0;
    sam::Transition* winner = 0;
    std::vector<sam::Transition> listWinners;
    float Q = 0, Qmax = 0;
    int randNumTrans;
    
    std::vector<sam::Transition>::iterator it_transition = listTransitions.begin();
    std::vector<sam::Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {    
        Transition& oTransition = *it_transition;
        std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
        GameState& oNextState = listGameStates.at(oTransition.getNextState()); 
        
        //Calculate the Q values and search for the one with the highest value
        Q = oLearn.computeQ(oNextState);
        it_transition->setQ(Q);

        LOG4CXX_INFO(logger, "next " << oNextState.toString());   
        LOG4CXX_INFO(logger, "Q=" << std::to_string(Q));
        
        if (Q > Qmax)
        {
            Qmax = Q;
            listWinners.clear();
            listWinners.push_back(oTransition);
            winner = &oTransition;
        }   
        // if various connections share the maximum confidence, take winner randomly among them
        else if (Q == Qmax)
        {
            listWinners.push_back(oTransition);
            
            randNumTrans = rand() % listWinners.size();
            winnerTemporal = &(listWinners.at(randNumTrans));
            winner = &(listTransitions.at(winnerTemporal->getID()));
        }
        it_transition++;
    }

    LOG4CXX_INFO(logger, "best transition = " << winner->toString());  

    return winner;
}


std::string Strategy2::toStringBestMove()
{
    return ("bestAttack: [reward=" + std::to_string(bestReward) + 
            ", move=(" + std::to_string(bestMove[0]) + "," + std::to_string(bestMove[1]) + ")]"); 
}

}