/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "TaskTree.h"

namespace sam 
{
log4cxx::LoggerPtr TaskTree::logger(log4cxx::Logger::getLogger("sam.player"));

    

void TaskTree::showTask(GameTask& oGameTask)
{
    // show the task
    LOG4CXX_INFO(logger, oGameTask.showData());

    std::vector<GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<GameState>::iterator it_end = oGameTask.getListGameStates().end();
    // show each task state
    while (it_gameState != it_end)
    {        
        showState(*it_gameState);
        it_gameState++;
    }    
}

void TaskTree::showState(GameState& oGameState)
{
    LOG4CXX_INFO(logger, oGameState.toString());

    std::vector<Transition>::iterator it_transition = oGameState.getListTransitions().begin();
    std::vector<Transition>::iterator it_end = oGameState.getListTransitions().end();
    // show each state transition
    while (it_transition != it_end)
    {    
        LOG4CXX_INFO(logger, it_transition->toString());
        it_transition++;
    }   
}

void TaskTree::showTask2(GameTask& oGameTask, bool bfilterOut)
{
    // show the task
    LOG4CXX_INFO(logger, oGameTask.showData());

    std::vector<GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<GameState>::iterator it_end = oGameTask.getListGameStates().end();
    // show each task state
    while (it_gameState != it_end)
    {        
        showState2(*it_gameState, oGameTask, bfilterOut);
        it_gameState++;
    }    
}

void TaskTree::showState2(GameState& oGameState, GameTask& oGameTask, bool bfilterOut)
{
    LOG4CXX_INFO(logger, oGameState.toStringBrief());    

    std::vector<Transition>::iterator it_transition = oGameState.getListTransitions().begin();
    std::vector<Transition>::iterator it_end = oGameState.getListTransitions().end();
    // show each state transition
    while (it_transition != it_end)
    {    
        showTransition2(*it_transition, oGameTask, bfilterOut);
        it_transition++;
    }   
}

void TaskTree::showTransition2(Transition& oTransition, GameTask& oGameTask, bool bfilterOut)
{
    // filter out transitions with zero Q
    if (bfilterOut && oTransition.getQ() == 0.0)
        return;
    
    int nextStateID = oTransition.getNextState();
    GameState& oNextState = oGameTask.getListGameStates().at(nextStateID);
    int* nextCells = oNextState.getCells();

    LOG4CXX_INFO(logger, "-> " + std::to_string(nextStateID) +  " (" + std::to_string(nextCells[0]) + "," + std::to_string(nextCells[1]) + "," + std::to_string(nextCells[2]) + ")" 
            + " Q=" + std::to_string((int)oTransition.getQ()));           
}


void TaskTree::getTaskQMatrix(cv::Mat& matQ, GameTask& oGameTask)
{
    matQ = cv::Scalar(0);
           
    // for each state, fill the corresponding Q matrix row
    for (auto& oGameState : oGameTask.getListGameStates()) 
    {
        cv::Mat matRow = matQ.row(oGameState.getID());
        fillQMatrixRow(matRow, oGameState);        
    }        
}

void TaskTree::fillQMatrixRow(cv::Mat& matRow, GameState& oGameState)
{
    // fill the Q row cells that correspond to a state transition
    for (auto& oTransition : oGameState.getListTransitions()) 
    {
        int j = oTransition.getNextState();
        matRow.at<int>(j) = (int)oTransition.getQ();        
    }                
}

}