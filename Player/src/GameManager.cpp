/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "GameManager.h"

namespace sam 
{
log4cxx::LoggerPtr GameManager::logger(log4cxx::Logger::getLogger("sam.player"));

GameManager::GameManager() {}

void GameManager::startModules()
{ 
    // game is started with 2 player agents (SAM & TAM) & first turn assigned randomly
    LOG4CXX_INFO(logger, "GameManager: starting modules ..."); 
    
    oSam.init(oBoard, "SAM");
    oSam.setFrequency(2.0);
    oSam.on();
    
    oTam.init(oBoard, "TAM");
    oTam.setFrequency(2.0);
    oTam.on();

    // init game assigning first turn
    oBoard.initTurn();
    oBoard.showStates();
    
    // Informer module added (stores game progress in DB for external monitoring)
    oInformer.init(oBoard);
    oInformer.setFrequency(1.25);
    oInformer.on();
}

void GameManager::stopModules()
{
    // players are asked to stop, then we wait for them to finish
    LOG4CXX_INFO(logger, "GameManager: stopping modules ..."); 

    oSam.off();
    oTam.off();
    oInformer.off();
    
    oSam.wait();
    oTam.wait();
    oInformer.wait();
}

bool GameManager::isGameOver()
{
    // checks board status to see if game has finished
    int status = oBoard.getStatus();
    return (status == GameBoard::eSTAT_FINISHED_DRAW || 
            status == GameBoard::eSTAT_FINISHED_SAM_WINS || 
            status == GameBoard::eSTAT_FINISHED_TAM_WINS);
}

}