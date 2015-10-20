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

void TaskTree::showTask2(GameTask& oGameTask)
{
    // show the task
    LOG4CXX_INFO(logger, oGameTask.showData());

    std::vector<GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<GameState>::iterator it_end = oGameTask.getListGameStates().end();
    // show each task state
    while (it_gameState != it_end)
    {        
        showState2(*it_gameState, oGameTask);
        it_gameState++;
    }    
}

void TaskTree::showState2(GameState& oGameState, GameTask& oGameTask)
{
    LOG4CXX_INFO(logger, oGameState.toStringBrief());    

    std::vector<Transition>::iterator it_transition = oGameState.getListTransitions().begin();
    std::vector<Transition>::iterator it_end = oGameState.getListTransitions().end();
    // show each state transition
    while (it_transition != it_end)
    {    
        showTransition2(*it_transition, oGameTask);
        it_transition++;
    }   
}

void TaskTree::showTransition2(Transition& oTransition, GameTask& oGameTask)
{
    int nextStateID = oTransition.getNextState();
    GameState& oNextState = oGameTask.getListGameStates().at(nextStateID);
    int* nextCells = oNextState.getCells();

    LOG4CXX_INFO(logger, "-----> (" + std::to_string(nextCells[0]) + "," + std::to_string(nextCells[1]) + "," + std::to_string(nextCells[2]) + ") " + std::to_string(nextStateID)
            + ", rwd=" + std::to_string((int)oNextState.getReward())  + ", Q=" + std::to_string((int)oTransition.getQ()));           
}

}