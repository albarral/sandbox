/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "GameManager.h"
#include "data/PlayerIdentity.h"

namespace sam 
{
log4cxx::LoggerPtr GameManager::logger(log4cxx::Logger::getLogger("sam.player"));

GameManager::GameManager() {}

void GameManager::startModules()
{ 
    // game is started with 2 player agents (SAM & TAM) & first turn assigned randomly
    LOG4CXX_INFO(logger, "GameManager: starting modules ..."); 
    
    // Define SAM's identity
    PlayerIdentity& oSamIdentity = oSam.getPlayerIdentity();
    oSamIdentity.setID("SAM");
    oSamIdentity.setMyMark(1);
    oSamIdentity.setPlayMode(PlayerIdentity::eMODE_SMART);
    oGameFlow.addPlayer(oSamIdentity);

    if (gameType == eGAME_SAM_VS_TAM)
    {
        // Define TAM's identity
        PlayerIdentity& oTamIdentity = oTam.getPlayerIdentity();
        oTamIdentity.setID("TAM");
        oTamIdentity.setMyMark(2);
        oTamIdentity.setPlayMode(PlayerIdentity::eMODE_SIMPLE);
        oGameFlow.addPlayer(oTamIdentity);
    }    
    else if (gameType == eGAME_SAM_VS_HUMAN)
    {
        // Define user's identity
        PlayerIdentity& oHumanIdentity = oTam.getPlayerIdentity();
        oHumanIdentity.setID("human");
        oHumanIdentity.setMyMark(2);
        oGameFlow.addPlayer(oHumanIdentity);
    }

    // init game flow & assign first turn randomly
    oGameFlow.initTurn();

    // init SAM agent
    oSam.init(oGameBoard, oGameFlow);
    oSam.setFrequency(2.0);
    oSam.on();

    if (gameType == eGAME_SAM_VS_TAM)
    {
        // init TAM agent    
        oTam.init(oGameBoard, oGameFlow);
        oTam.setFrequency(2.0);
        oTam.on();
    }
    
    // Informer module added (stores game progress in DB for external monitoring)
    oInformer.init(oGameBoard, oGameFlow);
    oInformer.setFrequency(2.0);
    oInformer.on();
}

void GameManager::stopModules()
{
    // players are asked to stop, then we wait for them to finish
    LOG4CXX_INFO(logger, "GameManager: stopping modules ..."); 

    oSam.off();
    if (gameType == eGAME_SAM_VS_TAM)
        oTam.off();
    oInformer.off();
    
    oSam.wait();
    if (gameType == eGAME_SAM_VS_TAM)
        oTam.wait();
    oInformer.wait();
    
    LOG4CXX_INFO(logger, "GameManager: SAM off ? " << oSam.isOff()); 
    if (gameType == eGAME_SAM_VS_TAM)
        LOG4CXX_INFO(logger, "GameManager: TAM off ? " << oTam.isOff()); 
    LOG4CXX_INFO(logger, "GameManager: Informer off ? " << oInformer.isOff()); 
}

// checks board status to see if game has finished
bool GameManager::isGameOver()
{
    return oGameFlow.isGameOver();
}

}