#ifndef __SAM_PLAYER_BOARDACTUATOR_H
#define __SAM_PLAYER_BOARDACTUATOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include <log4cxx/logger.h>

#include "sam/player/data/GameBoard.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace player
{     
// Class used to update the board state in DB (in TAB_BOARD table).
class BoardActuator
{
private:
    static log4cxx::LoggerPtr logger;
    utilsDB::Database oDatabase;
    sql::Connection* con;
    std::string updateBoard;
    std::string selectMaxTryID;

public:
    BoardActuator();
    ~BoardActuator();
    
    // writes new movement to TAB_BOARD
    void writeMove (GameBoard& oGameBoard, std::string playerID, int boardStatus);
    // update board status of last move
    void updateLastMoveStatus (int boardStatus);
    // clears TAB_BOARD
    void clearGameHistory();        
    
private:
    bool connect();    
    
};
}
}

#endif
