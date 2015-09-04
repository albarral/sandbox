/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp" //for the matrix

#include "Informer.h"
#include "GameManager.h"
#include "Strategy.h"

namespace sam 
{
log4cxx::LoggerPtr Informer::logger(log4cxx::Logger::getLogger("sam.player"));

Informer::Informer() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
}

Informer::~Informer()
{
    oDatabase.closeConnectionDB();        
}

void Informer::init(GameBoard& oBoard)
{  
    LOG4CXX_INFO(logger, "Informer initialized");     
    pBoard = &oBoard;
};

void Informer::first()
{
    // we first connect to DB & clear the last game history
    con = oDatabase.getConnectionDB(); 
    clearGameHistory();
}

void Informer::loop()
{
    // Look which state have GameBoard and save it on database
    storeGameState();
}

// stores in DB the present state of the game board (TAB_BOARD)
void Informer::storeGameState()
{
    cv::Mat matrix = pBoard->getMatrix();
    
    moveID++;
    
    // insert new move (without cells info)
    std::string insert = "INSERT INTO TAB_BOARD (tryID, boardStatus) VALUES (" + std::to_string(moveID) 
            + ", " + std::to_string(pBoard->getStatus()) + ")";
    oDatabase.update(insert, con);

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


// clears from DB the stored info of last game (TAB_BOARD)
void Informer::clearGameHistory()
{
    std::string del = "delete from TAB_BOARD where tryID >= 0";
    oDatabase.update(del, con);
    con->commit();
    moveID = 0;
}


}