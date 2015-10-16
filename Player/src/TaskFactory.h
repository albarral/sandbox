#ifndef __SAM_PLAYER_TASKFACTORY_H
#define __SAM_PLAYER_TASKFACTORY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "Transition.h"

namespace sam 
{
class TaskFactory
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
    TaskFactory();
    
    static void buildTicTacToeTask(GameTask& oGameTask);    
    
    // shows brief description of given task
    static void describeTask(GameTask& oGameTask);    
    // shows brief description of given state
    static void describeState(GameState& oGameState);

};
}

#endif
