#ifndef __SAM_INFORMER_H
#define __SAM_INFORMER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "utils/module2.h"
#include "data/GameBoard.h"
#include "data/GameFlow.h"
#include "sam/utils/Database.h"

namespace sam 
{
// Module that continuously stores in DB the state of the ongoing game (in TAB_BOARD table).
// This storage allows for external access to the game's progress and for later analysis of the game moves.
// It derives from base class Module2
class Informer : public Module2
{
private:
    static log4cxx::LoggerPtr logger;
    GameBoard* pGameBoard;      // pointer to the game's board
    GameFlow* pGameFlow;  // pointer to the game's flow   
    Database oDatabase;
    sql::Connection* con;
    int moveID;     // ID of each register

public:
    Informer();
    ~Informer();
    
    // initializes the module 
    void init (GameBoard& oGameBoard, GameFlow& oGameFlow);
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();   
    
    // stores in DB the present state of the game board (TAB_BOARD)
    void storeGameState();
    // clears from DB the stored info of last game (TAB_BOARD)
    void clearGameHistory();        
    // gets from DB the ID of the most recent stored game state (TAB_BOARD)
    int getMostRecentElement();
};
}
#endif
