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
    oSam.init();
    oSam.setFrequency(2.0);
    oSam.on();
    
    oTam.init();
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
    if(oBoard.getStatus() == 0 || oBoard.getStatus() == 1 || oBoard.getStatus() == 2)
    {
        return false;
    }
    else return true;
}

}