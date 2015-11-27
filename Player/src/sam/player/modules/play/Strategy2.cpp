/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "sam/player/modules/play/Strategy2.h"
#include "sam/player/modules/play/PlayerActions.h"
#include "sam/player/data/GameBoard.h"

namespace sam
{    
namespace player
{         
log4cxx::LoggerPtr Strategy2::logger(log4cxx::Logger::getLogger("sam.player"));

Strategy2::Strategy2() 
{
    benabled = false;
    setExplorativeMode(false);
}

void Strategy2::init(GameTask& oGameTask)
{
    pGameTask = &oGameTask;
    benabled = true;
    oLearn.setGamma(0.0);

    LOG4CXX_INFO(logger, "Strategy2 enabled");      
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
    // explorative mode: select random line for the action
    if (bexplorative)
    {
        actionLine = rand() % Line::eLINE_DIM;
        LOG4CXX_INFO(logger, "explore: action line " << actionLine);   
    }

    // check rows
    LOG4CXX_INFO(logger, "CHECK ROWS .....");   
    for (int i=0; i<matrix.rows; i++)
    {
        // analyse row & check proper moves in it
        oLine.checkRow(i, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eTYPE_ROW, i, oLine);
    }    

    // check columns
    LOG4CXX_INFO(logger, "CHECK COLUMNS .....");   
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check proper moves in it
        oLine.checkColumn(j, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eTYPE_COL, j, oLine);
    }    
    
    // check diagonals
    LOG4CXX_INFO(logger, "CHECK DIAGONALS .....");   
    // analyse first diagonal & check proper moves in it
    int lineType = Line::eTYPE_DIAG1;
    oLine.checkDiagonal(lineType, myMark, GameBoard::EMPTY_MARK);        
    checkBestMoveInLine(lineType, 0, oLine);

    // analyse second diagonal & check proper moves in it
    lineType = Line::eTYPE_DIAG2;
    oLine.checkDiagonal(lineType, myMark, GameBoard::EMPTY_MARK);        
    checkBestMoveInLine(lineType, 0, oLine);
    
    LOG4CXX_INFO(logger, toStringBestMove());      
}


// checks if the given line holds the best move in the board 
void Strategy2::checkBestMoveInLine(int lineType, int linePosition, Line& oLine)
{
    bool bUpdateBest = false;  // indicates the best move has to be updated
    PlayerActions oPlayerActions;

    LOG4CXX_INFO(logger, "> line " << linePosition);   
    
    // analyzes the line to obtain its best transition
    learn::Transition* pBestTransition = analyseLine(oLine);    
        
    // if line transition was found ...
    if (pBestTransition != 0)
    {
        // explorative mode: update best move if this is the randomly selected line
        if (bexplorative)
        {
            int lineID = Line::getLineIdentifier(lineType, linePosition);
            bUpdateBest = (lineID == actionLine);
        }
        // normal mode: update best move if this is the best transition till the moment
        else
        {
            bUpdateBest = (pBestTransition->getQ() > bestReward);                                    
        }                
        
        // if best move to be updated
        if (bUpdateBest)
        {
            LOG4CXX_INFO(logger, ">>> UPDATE BEST!");               
            bestReward = pBestTransition->getQ();
                        
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
                    case Line::eTYPE_ROW:
                        oPlayerActions.applyAction2Row(linePosition, x, y);
                        break;
                    case Line::eTYPE_COL:
                        oPlayerActions.applyAction2Column(linePosition, x, y);
                        break;
                    case Line::eTYPE_DIAG1:
                    case Line::eTYPE_DIAG2:
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
learn::Transition* Strategy2::analyseLine(Line& oLine)
{
    // find state for given line
    GameState* pDeducedState = deduceState4Line(oLine);
            
    if (pDeducedState == 0)
    {
        LOG4CXX_WARN(logger, "analyseLine: no state deduced from Line");   
        return 0;
    }
    
    LOG4CXX_INFO(logger, pDeducedState->toStringBrief());    
    
    // from the present state, find the best possible transition
    return (findBestTransition(*pDeducedState));
}


GameState* Strategy2::deduceState4Line(Line& oLine)
{
    GameState* pGameState = 0;
    int* lineCells = oLine.getCells();

    // Find the game state that represents the given Line configuration
    std::vector<GameState>::iterator it_gameState = pGameTask->getListGameStates().begin();
    std::vector<GameState>::iterator it_end = pGameTask->getListGameStates().end();
    while (it_gameState != it_end)
    {        
        int* stateCells = it_gameState->getCells();

        if (stateCells[0] == lineCells[0] && stateCells[1] == lineCells[1] && stateCells[2] == lineCells[2])
        {
            pGameState = &(*it_gameState);
            break;
        }
        it_gameState++;
    }    
    
    return pGameState;
}

// Compute the Q value of all transitions from this state and return the best one
learn::Transition* Strategy2::findBestTransition(GameState& oFromState)
{
    learn::Transition* winner = 0;
    float Q = 0, Qmax = 0.0;
    int randTrans;
    
    // if no transitions from this state return nothing
    if (oFromState.getListTransitions().size() == 0)
    {
        LOG4CXX_WARN(logger, "findBestTransition: state without transitions");   
        return 0;
    }
    
    std::vector<learn::Transition>& listTransitions = oFromState.getListTransitions();

    // walk transitions list computing their Q value
    std::vector<learn::Transition>::iterator it_transition = listTransitions.begin();
    std::vector<learn::Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {    
        learn::Transition& oTransition = *it_transition;
        
        GameState& oToState = pGameTask->getListGameStates().at(oTransition.getNextState()); 
        
        //Calculate the Q values and search for the one with the highest value
        Q = oLearn.computeQ(oToState);
        it_transition->setQ(Q);
        
        //LOG4CXX_DEBUG(logger, "-> " << std::to_string(it_transition->getNextState()) << " Q=" << std::to_string((int)Q));

        // track best option
        if (Q > Qmax)
        {
            Qmax = Q;
            winner = &oTransition;
        }   
        it_transition++;
    }

    // on explorative mode, take any transition
    if (bexplorative)
    {
        randTrans = rand() % listTransitions.size();
        winner = &(listTransitions.at(randTrans));
    }    
    // all transitions will zero Q, take first
    else if (Qmax == 0.0)
        winner = &(listTransitions.at(0));
    
    LOG4CXX_INFO(logger, "best " << winner->toStringBrief());  

    return winner;
}


std::string Strategy2::toStringBestMove()
{
    return ("bestMove: [reward=" + std::to_string(bestReward) + 
            ", move=(" + std::to_string(bestMove[0]) + "," + std::to_string(bestMove[1]) + ")]"); 
}

}
}