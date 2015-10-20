#ifndef __SAM_PLAYER_BOARDSENSOR_H
#define __SAM_PLAYER_BOARDSENSOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include <log4cxx/logger.h>

#include "data/GameBoard.h"
#include "sam/utils/Database.h"

namespace sam 
{
// Class used to read the board state from DB (in TAB_BOARD table).
class BoardSensor 
{
private:
    static log4cxx::LoggerPtr logger;
    int moveID;                        // number of last sensed move 
    std::string movedPlayer;     // player ID of the last sensed move 
    int status;                          // status of the last sensed move                    
    Database oDatabase;
    sql::Connection* con;
    std::string selectMoves;

public:
    BoardSensor();
    ~BoardSensor();
    
    // senses the board 
    void senseBoard (GameBoard& oGameBoard);
    
    std::string getLastMovePlayer() {return movedPlayer;};
    int getLastMoveNumber() {return moveID;};    
    int getLastMoveStatus() {return status;};    
    
private:
    bool connect();
};
}
#endif
