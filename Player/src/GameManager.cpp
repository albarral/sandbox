/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "GameManager.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr GameManager::logger(Logger::getLogger("sam.game"));

GameManager::GameManager() 
{}

void GameManager::startModules()
{ 
    GameBoard& refBoard = oBoard;
    std::string name;
    
    int assignTurn = rand() % 2; //value 0 or 1
    if(assignTurn == 0)
        oBoard.setStatus(sam::GameBoard::eSTAT_TURN_SAM);
    else oBoard.setStatus(sam::GameBoard::eSTAT_TURN_TAM);
    oBoard.showStates();
    
    name = "SAM";
    oSam.init(refBoard, name);
    oSam.setFrequency(2.0);
    oSam.on();
    
    name = "TAM";
    oTam.init(refBoard, name);
    oTam.setFrequency(2.0);
    oTam.on();
}

void GameManager::stopModules()
{
    oSam.off();
    oSam.wait();
    
    oTam.off();
    oTam.wait();
}

bool GameManager::isGameOver()
{   
    if(oBoard.getStatus() == sam::GameBoard::eSTAT_READY || oBoard.getStatus() == sam::GameBoard::eSTAT_TURN_SAM 
            || oBoard.getStatus() == sam::GameBoard::eSTAT_TURN_TAM)
    {
        return false;
    }
    else return true;
}

}