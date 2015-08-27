/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <cstdlib>  //for the random values

#include "GameManager.h"

namespace sam 
{
log4cxx::LoggerPtr GameManager::logger(log4cxx::Logger::getLogger("sam.player"));

GameManager::GameManager() {}

void GameManager::startModules()
{ 
    std::string name;
    
    int assignTurn = rand() % 2; //value 0 or 1
    if (assignTurn == 0)
        oBoard.setStatus(sam::GameBoard::eSTAT_TURN_SAM);
    else 
        oBoard.setStatus(sam::GameBoard::eSTAT_TURN_TAM);
    
    oBoard.showStates();
    
    name = "SAM";
    oSam.init(oBoard, name);
    oSam.setFrequency(2.0);
    oSam.on();
    
    name = "TAM";
    oTam.init(oBoard, name);
    oTam.setFrequency(2.0);
    oTam.on();
}

void GameManager::stopModules()
{
    oSam.off();
    oTam.off();
    
    oSam.wait();
    oTam.wait();
}

bool GameManager::isGameOver()
{   
    int status = oBoard.getStatus();
    return (status == sam::GameBoard::eSTAT_FINISHED_DRAW || status == sam::GameBoard::eSTAT_FINISHED_SAM_WINS 
            || status == sam::GameBoard::eSTAT_FINISHED_TAM_WINS);
}

}