#ifndef __SAM_PLAYER_VIRTUALWATCHER_H
#define __SAM_PLAYER_VIRTUALWATCHER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarra@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/modules/watch/BoardWatcher.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace player
{    
// Specific BoardWatcher class used to watch a virtual tic-tac-toe board.
// The virtual board is represented by a database table (named TAB_VIRTUAL_BOARD).
class VirtualWatcher : public BoardWatcher
{
private:
    utilsDB::Database oDatabase;
    sql::Connection* con;
    std::string selectBoard;

public:
    VirtualWatcher();
    ~VirtualWatcher();
    
    // senses the virtual board 
    virtual bool senseBoard();
    // searches the virtual board
    virtual bool searchBoard();
        
private:
    bool connectDB();
};
}
}
#endif
