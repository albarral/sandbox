#ifndef __SAM_PLAYER_VIRTUALMOVER_H
#define __SAM_PLAYER_VIRTUALMOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "sam/utilsDB/DBClient.h"

namespace sam 
{
namespace player
{     
// Specific BoardMover class used to actuate over a virtual tic-tac-toe board.
// The virtual board is represented by a database table (named TAB_VIRTUAL_BOARD).
class VirtualMover
{
private:
    static log4cxx::LoggerPtr logger;
    utilsDB::DBClient* pDatabase;
    std::string updateBoard;

public:
    VirtualMover();
    ~VirtualMover();
    
    // Puts a piece of specific type in the given board position (row, col)
    void putPiece (int row, int col, int pieceType);
    // Removes a piece of any type from the given board position (row, col)
    void removePiece (int row, int col);
    
private:
    // connects to DB
    bool connectDB();        
};

}
}

#endif
