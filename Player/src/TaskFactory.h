#ifndef __SAM_PLAYER_T3TASK_H
#define __SAM_PLAYER_T3TASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "learn/GameTask.h"

namespace sam 
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

#endif
