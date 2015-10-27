/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Strategy2.h"
#include "PlayerActions.h"
#include "data/GameBoard.h"
#include "utils/TaskTree.h"

namespace sam
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

// Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
void Strategy2::playSmart(cv::Mat& matrix, int myMark)
{   
    if(bexplorative)
    {
        int randNum = rand() % 8;
        setSelectedLine(randNum);  
        LOG4CXX_INFO(logger, "numero de linea " << randNum);   
    }
    
    listExploredTransitions.clear();
    Line oLine;
    oLine.setMatrix(matrix);

    LOG4CXX_INFO(logger, "Strategy2: play smart ...");   
    TaskTree::showTask2(*pGameTask, true);

    // zero reward before the analysis
    bestReward = 0.0;

    // check rows
    LOG4CXX_INFO(logger, "CHECK ROWS .....");   
    for (int i=0; i<matrix.rows; i++)
    {
        // analyse row & check proper moves in it
        oLine.checkRow(i, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eLINE_ROW, i, oLine);
    }    

    // check columns
    LOG4CXX_INFO(logger, "CHECK COLUMNS .....");   
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check proper moves in it
        oLine.checkColumn(j, myMark, GameBoard::EMPTY_MARK);        
        checkBestMoveInLine(Line::eLINE_COL, j, oLine);
    }    
    
    // check diagonals
    LOG4CXX_INFO(logger, "CHECK DIAGONALS .....");   
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
    int total;

    LOG4CXX_INFO(logger, "> line " << linePosition);   
    
    // analyzes the line to obtain its best transition
    Transition* pBestTransition = analyseLine(oLine);
    Transition& oBestTransition = *pBestTransition;    
    
    if(bexplorative)
    {
        if (lineType == 0)
            total = lineType + linePosition;
        else if (lineType == 1)
            total = lineType + 2 + linePosition;
        else if (lineType == 2)
            total = 6;
        else if (lineType == 3)
            total = 7;
               
        if(pBestTransition != 0)
            listExploredTransitions.push_back(oBestTransition);
        
        if (pBestTransition != 0 && (total == selectedLine))
        {
            findBestMove(oBestTransition, lineType, linePosition, oLine);
        }
        else if (pBestTransition == 0 && (total == selectedLine))  // CUANDO LA SELECTEDLINE SEA LA 0 NO HABRÁ LISTA
        {
            int randNum = rand() % listExploredTransitions.size();
            pBestTransition = &(listExploredTransitions.at(randNum));
            Transition& oBestTransition = *pBestTransition; 
            findBestMove(oBestTransition, lineType, linePosition, oLine);
        }
        
    }
    // if line transition was found ...
    else if (pBestTransition != 0 && !bexplorative)
    {
        maxLineReward = pBestTransition->getQ();
        
        // and it's the best transition till the moment
        if (maxLineReward > bestReward)
        {
            LOG4CXX_INFO(logger, ">>> BEST!");               
            bestReward = maxLineReward;
            
            findBestMove(oBestTransition, lineType, linePosition, oLine);
                        
//            // deduce the action that causes this transition
//            GameState& state1 = pGameTask->getListGameStates().at(pBestTransition->getStateID());
//            GameState& state2 = pGameTask->getListGameStates().at(pBestTransition->getNextState());                        
//            // deduce it in the line's domain
//            if (oPlayerActions.getActions4Transition(state1, state2) > 0)
//            {
//                int x, y;
//                
//                // then translate it to the board's domain
//                switch (lineType)
//                {
//                    case Line::eLINE_ROW:
//                        oPlayerActions.applyAction2Row(linePosition, x, y);
//                        break;
//                    case Line::eLINE_COL:
//                        oPlayerActions.applyAction2Column(linePosition, x, y);
//                        break;
//                    case Line::eLINE_DIAG1:
//                    case Line::eLINE_DIAG2:
//                        oPlayerActions.applyAction2Diagonal(lineType, x, y);
//                        break;                                                
//                }
//                        
//                // store this best move till now
//                bestMove[0] = y;   // y stores the row
//                bestMove[1] = x;   // x stores the column
//            }
        }
    }    
}


// (CORE OF THE SMART STRATEGY)
// Uses the learned knowledge about the task to obtain the best rewarded transition in this line
Transition* Strategy2::analyseLine(Line& oLine)
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
    std::vector<sam::GameState>::iterator it_gameState = pGameTask->getListGameStates().begin();
    std::vector<sam::GameState>::iterator it_end = pGameTask->getListGameStates().end();
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
Transition* Strategy2::findBestTransition(GameState& oFromState)
{
    sam::Transition* winner = 0;
    float Q = 0, Qmax = 0.0;
    //sam::Transition* winnerTemporal = 0;
    //std::vector<sam::Transition> listWinners;
    int randTrans;
    
    // if no transitions from this state return nothing
    if (oFromState.getListTransitions().size() == 0)
    {
        LOG4CXX_WARN(logger, "findBestTransition: state without transitions");   
        return 0;
    }
    
    std::vector<Transition>& listTransitions = oFromState.getListTransitions();

    // walk transitions list computing their Q value
    std::vector<sam::Transition>::iterator it_transition = listTransitions.begin();
    std::vector<sam::Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {    
        Transition& oTransition = *it_transition;
        
        GameState& oToState = pGameTask->getListGameStates().at(oTransition.getNextState()); 
        
        //Calculate the Q values and search for the one with the highest value
        Q = oLearn.computeQ(oToState);
        it_transition->setQ(Q);
        
        //LOG4CXX_INFO(logger, "next " << oNextState.toString());   
        LOG4CXX_DEBUG(logger, "-> " << std::to_string(it_transition->getNextState()) << " Q=" << std::to_string((int)Q));

        // track best option
        if (Q > Qmax)
        {
            Qmax = Q;
            winner = &oTransition;
            //listWinners.clear();
            //listWinners.push_back(oTransition);
        }   
//        // if various connections share the maximum confidence, take winner randomly among them
//        else if (Q == Qmax)
//        {
//            listWinners.push_back(oTransition);
//            
//            randNumTrans = rand() % listWinners.size();
//            winnerTemporal = &(listWinners.at(randNumTrans));
//            winner = &(listTransitions.at(winnerTemporal->getID()));
//        }
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

void Strategy2::findBestMove(Transition& oBestTransition, int lineType, int linePosition, Line& oLine)
{
    PlayerActions oPlayerActions;
    
    // deduce the action that causes this transition
            GameState& state1 = pGameTask->getListGameStates().at(oBestTransition.getStateID());
            GameState& state2 = pGameTask->getListGameStates().at(oBestTransition.getNextState());                        
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

std::string Strategy2::toStringBestMove()
{
    return ("bestMove: [reward=" + std::to_string(bestReward) + 
            ", move=(" + std::to_string(bestMove[0]) + "," + std::to_string(bestMove[1]) + ")]"); 
}

}