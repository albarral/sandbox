#ifndef __SAM_PLAYER_TASKTREE_H
#define __SAM_PLAYER_TASKTREE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "Transition.h"

namespace sam 
{
class TaskTree
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
    TaskTree();
        
    // shows full description of given task
    static void showTask(GameTask& oGameTask);    
    // shows full description of given state
    static void showState(GameState& oGameState);
    
    // shows brief description of given task
    static void showTask2(GameTask& oGameTask, bool bfilterOut = false);    
    // shows brief description of given state
    static void showState2(GameState& oGameState, GameTask& oGameTask, bool bfilterOut);
    // shows brief description of given transition
    static void showTransition2(Transition& oTransition, GameTask& oGameTask, bool bfilterOut);

};
}

#endif
