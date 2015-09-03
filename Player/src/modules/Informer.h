#ifndef __SAM_INFORMER_H
#define __SAM_INFORMER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "utils/module2.h"
#include "data/GameBoard.h"
#include "sam/utils/Database.h"

namespace sam 
{
// It derives from base class Module2
class Informer : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    GameBoard* pBoard;      // pointer to the game's board
    Database oDatabase;
    sql::Connection* con;
    int numberTry;

public:
    Informer();
    
    // initializes the module 
    void init (GameBoard& oBoard);
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();   
    
    void storeInMemo();
    void loadFromMemo();
};
}
#endif
