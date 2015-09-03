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

void Informer::init(GameBoard& oBoard)
{  
    pBoard = &oBoard;
    numberTry = 0;
};

void Informer::first()
{
    con = oDatabase.getConnectionDB(); 
    loadFromMemo();
    if(numberTry > 0)
        numberTry = numberTry +1;
}

void Informer::loop()
{
    // Look which state have GameBoard and save it on database
    storeInMemo();
    
    int status = pBoard->getStatus();
    if (status == GameBoard::eSTAT_FINISHED_DRAW || status == GameBoard::eSTAT_FINISHED_SAM_WINS || 
            status == GameBoard::eSTAT_FINISHED_TAM_WINS)
    {
        con->commit();
        oDatabase.closeConnectionDB();
    }
}

void Informer::storeInMemo()
{
    cv::Mat matrix = pBoard->getMatrix();
    
    std::string insert = "INSERT INTO TAB_BOARD (IDtry, StatusBoard) VALUES (" + std::to_string(numberTry) 
            + ", " + std::to_string(pBoard->getStatus()) + ")";
    oDatabase.update(insert, con);

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            std::string update = "UPDATE TAB_BOARD SET Cell" + std::to_string(i) + std::to_string(j) + " = " 
                    + std::to_string(matrix.at<int>(i,j)) + " WHERE IDtry = " + std::to_string(numberTry);
            oDatabase.update(update, con);
        }
    }        
    numberTry ++;
}

void Informer::loadFromMemo()
{
    std::string sel = "SELECT * FROM TAB_BOARD ";
    sql::ResultSet* res = oDatabase.select(sel, con);
       
    while (res->next())
    {
        numberTry = res->getInt("IDtry");
    }
    
}

}