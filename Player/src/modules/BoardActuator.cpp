/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp" //for the matrix

#include "BoardActuator.h"

namespace sam 
{
log4cxx::LoggerPtr BoardActuator::logger(log4cxx::Logger::getLogger("sam.player"));

BoardActuator::BoardActuator() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    con = 0;
    updateBoard =  "INSERT INTO TAB_BOARD (boardStatus, player) VALUES (";
    selectMaxTryID = "SELECT MAX(tryID) FROM TAB_BOARD";
}

BoardActuator::~BoardActuator()
{
    oDatabase.closeConnectionDB();        
}

bool BoardActuator::connect()
{
    // if not connected or connection closed, reconnect
    if (con == 0 || con->isClosed())        
        con = oDatabase.getConnectionDB();
    
    // true if connection ok
    return (con != 0); 
}


void BoardActuator::writeMove (GameBoard& oGameBoard, std::string playerID, int boardStatus)
{        
    int moveID;
    
    // try reconnection
    if (!connect())
    {
        LOG4CXX_ERROR(logger, "BoardActuator: failed connection!");
        return;
    }

    cv::Mat matrix = oGameBoard.getMatrix();
    
    // insert new move (without cells info)
    std::string insert = updateBoard + std::to_string(boardStatus) + ", '" + playerID + "' )";
    oDatabase.update(insert, con);

    sql::ResultSet* res = oDatabase.select(selectMaxTryID, con);

    if (res->next())
        moveID = res->getInt(1);
    
    // update cells info
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            std::string update = "UPDATE TAB_BOARD SET Cell" + std::to_string(i) + std::to_string(j) + " = " 
                    + std::to_string(matrix.at<int>(i,j)) + " WHERE tryID = " + std::to_string(moveID);
            oDatabase.update(update, con);
        }
    }  
    con->commit();
}


void BoardActuator::updateLastMoveStatus(int boardStatus)
{        
    int moveID;
    
    // try reconnection
    if (!connect())
    {
        LOG4CXX_ERROR(logger, "BoardActuator: failed connection!");
        return;
    }

    sql::ResultSet* res = oDatabase.select(selectMaxTryID, con);

    if (res->next())
        moveID = res->getInt(1);

    std::string update = "UPDATE TAB_BOARD SET boardStatus = " + std::to_string(boardStatus) +
            " WHERE tryID = " + std::to_string(moveID);
    oDatabase.update(update, con);

    con->commit();
}


// clears from DB the stored info of last game (TAB_BOARD)
void BoardActuator::clearGameHistory()
{
    LOG4CXX_INFO(logger, "Clear game history");     

    // try reconnection
    if (!connect())
    {
        LOG4CXX_ERROR(logger, "BoardActuator: failed connection!");
        return;
    }

    std::string del = "delete from TAB_BOARD where tryID >= 0";
    oDatabase.update(del, con);
    con->commit();
}


}