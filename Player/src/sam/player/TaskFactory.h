#ifndef __SAM_PLAYER_TASKFACTORY_H
#define __SAM_PLAYER_TASKFACTORY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/learn/GameTask.h"

namespace sam 
{
namespace player
{    
class TaskFactory
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
    TaskFactory();
    
    static void buildTicTacToeTask(GameTask& oGameTask);    
    
};
}
}

#endif
