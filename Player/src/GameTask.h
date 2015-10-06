#ifndef __SAM_GAMETASK_H
#define __SAM_GAMETASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "Task.h"
#include "sam/utils/Database.h"

namespace sam 
{
class GameTask : public Task
{
public:
    // Tasks
    enum eType
    {
        eTASK_TICTACTOE
    };    
private:
    static log4cxx::LoggerPtr logger;
    Database oDatabase;
    
public:
    GameTask();
    
    void init(int ID);
    
private:
    void create();
    void storeInMemo();
    void loadFromMemo();
    
    void buildTicTacToe();
};
}

#endif
