/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp" //for the matrix
#include "log4cxx/ndc.h"

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

void Informer::init(GameBoard& oGameBoard, GameFlow& oGameFlow)
{  
    LOG4CXX_INFO(logger, "Informer initialized");     
    pGameBoard = &oGameBoard;
    pGameFlow = &oGameFlow;    
};

void Informer::first()
{
    log4cxx::NDC::push("Informer");   	
    // we first connect to DB & clear the last game history
    con = oDatabase.getConnectionDB(); 
    clearGameHistory();
    moveID = -1;
}

void Informer::loop()
{
    // If number of moves has changed store new values of board cells in database
    if(pGameFlow->getNumMoves() != moveID)
    {
        moveID = pGameFlow->getNumMoves();
        
        storeGameState();
    }
}

// stores in DB the present state of the game board (TAB_BOARD)
void Informer::storeGameState()
{
    LOG4CXX_INFO(logger, "Store game state - move " << moveID);     

    cv::Mat matrix = pGameBoard->getMatrix();
        
    // insert new move (without cells info)
    std::string insert = "INSERT INTO TAB_BOARD (tryID, boardStatus, turn) VALUES (" + std::to_string(moveID) 
            + ", " + std::to_string(pGameFlow->getStatus()) + ", " + std::to_string(pGameFlow->getTurn()) + ")";
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
    LOG4CXX_INFO(logger, "Clear game history");     

    std::string del = "delete from TAB_BOARD where tryID >= 0";
    oDatabase.update(del, con);
    con->commit();
    moveID = 0;
}


}