/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/BoardSensor.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr BoardSensor::logger(log4cxx::Logger::getLogger("sam.player"));

BoardSensor::BoardSensor() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    con = 0;
    selectMoves = "SELECT * FROM TAB_BOARD order by tryID desc";
}

BoardSensor::~BoardSensor()
{
    oDatabase.closeConnectionDB();        
}

bool BoardSensor::connect()
{
    // if not connected or connection closed, reconnect
    if (con == 0 || con->isClosed())        
        con = oDatabase.getConnectionDB();
    
    // true if connection ok
    return (con != 0); 
}

void BoardSensor::senseBoard(GameBoard& oGameBoard)
{  
    // try reconnection
    if (!connect())
    {
        LOG4CXX_ERROR(logger, "BoardSensor: failed connection!");
        return;
    }

    sql::ResultSet* res = oDatabase.select(selectMoves, con);
      
    // The first result is the last move, we take this one
    if (res->next())
    {       
        moveID = res->getInt("tryID");
        movedPlayer = res->getString("player");
        status = res->getInt("boardStatus");
        oGameBoard.markCell(res->getInt("Cell00"), 0, 0);
        oGameBoard.markCell(res->getInt("Cell01"), 0, 1);
        oGameBoard.markCell(res->getInt("Cell02"), 0, 2);
        oGameBoard.markCell(res->getInt("Cell10"), 1, 0);
        oGameBoard.markCell(res->getInt("Cell11"), 1, 1);
        oGameBoard.markCell(res->getInt("Cell12"), 1, 2);
        oGameBoard.markCell(res->getInt("Cell20"), 2, 0);
        oGameBoard.markCell(res->getInt("Cell21"), 2, 1);
        oGameBoard.markCell(res->getInt("Cell22"), 2, 2);
    }
}

}
}