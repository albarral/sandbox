/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/GameAnalyser.h"
#include "sam/player/data/GameDefs.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr GameAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

GameAnalyser::GameAnalyser() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    pGameBoard = 0;
}

void GameAnalyser::init(GameBoard& oGameBoard, GameAction& oGameAction)
{
    pGameBoard = &oGameBoard;
    pGameAction = &oGameAction;
    binitialized = true;
    LOG4CXX_INFO(logger, "GameAnalyser initialized");     
};

void GameAnalyser::first()
{    
    log4cxx::NDC::push("GameAnalyser");   	
    log4cxx::NDC::push("()");   	

    // we start in WAITING state
    if (binitialized && isConnected())
    {
        LOG4CXX_INFO(logger, "first ... ");  
        setState(GameAnalyser::eSTATE_WAITING);    
        showStateChange();        
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        Module::off();        
    }
}

void GameAnalyser::loop()
{   
    // read bus
    senseBus();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case GameAnalyser::eSTATE_WAITING:
                        
            if (checkBoardStable())
            {
                pGameBoard->getChangedLinesCopy(lines2Check);
                // CO_RESET_CHANGES = 1
                setState(GameAnalyser::eSTATE_ANALYSING);                    
            }            
            break;
            
        case GameAnalyser::eSTATE_ANALYSING:

            if (checkBoardStable())
            {
                processBoardChanges();         
                setState(GameAnalyser::eSTATE_DONE);              
            }
            else
            {
                setState(GameAnalyser::eSTATE_WAITING);              
            }
            break;

        case GameAnalyser::eSTATE_DONE:
                        
            if (checkBoardStable() == false)
            {
                setState(GameAnalyser::eSTATE_WAITING);              
            }
            break;
    }   // end switch    
    
    if (isStateChanged())
    {
        showStateChange();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void GameAnalyser::senseBus()
{
    // read control inputs: 
    // CO_INHIBIT_WATCHER
    binhibited = pBus->getCOBus().getCO_INHIBIT_WATCHER().checkRequested();
    // CO_RESET_WATCHER
    if (pBus->getCOBus().getCO_RESET_WATCHER().checkRequested())
    {
        LOG4CXX_INFO(logger, "reset watcher requested");     
        pGameBoard->resetChangedLines();
    }
}

void GameAnalyser::writeBus()
{
    // write sensor outputs: 
//    // SO_WATCHER_STATE
//    pBus->getSOBus().getSO_WATCHER_STATE().setValue(getState());
//    // SO_TIME_STABLE
//    pBus->getSOBus().getSO_STABLE_TIME().setValue(timeStable);
}

bool GameAnalyser::checkBoardStable()
{
    // TO DO ...    
    return true;
}

void GameAnalyser::processBoardChanges()
{
    LOG4CXX_DEBUG(logger, "process board changes ...");     

    // TO DO ...
}


// Shows the next state name
void GameAnalyser::showStateChange()
{
    std::string stateName;
    switch (getState())
    {
        case GameAnalyser::eSTATE_WAITING:
            stateName = "(waiting)";
            break;
            
        case GameAnalyser::eSTATE_ANALYSING:
            stateName = "(analysing)";
            break;

        case GameAnalyser::eSTATE_DONE:
            stateName = "(done)";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(stateName);   	
}

}
}