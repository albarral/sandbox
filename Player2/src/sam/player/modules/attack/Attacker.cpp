/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "log4cxx/ndc.h"

#include "sam/player/modules/attack/Attacker.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr Attacker::logger(log4cxx::Logger::getLogger("sam.player"));

Attacker::Attacker() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    pGameAction = 0;
    pPlayerData = 0;
}

Attacker::~Attacker() 
{
}

void Attacker::init(GameAction& oGameAction, PlayerData& oPlayerData)
{
    pGameAction = &oGameAction;
    pPlayerData = &oPlayerData;
    LOG4CXX_INFO(logger, "Attacker initialized");     
};

void Attacker::first()
{    
    log4cxx::NDC::push("Attacker");   	

    // we start in DONE state
    if (binitialized && isConnected())
    {
        LOG4CXX_INFO(logger, "started");  
        setState(Attacker::eSTATE_DONE);    
        setPrevState(Attacker::eSTATE_DONE);    
        showStateName();
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        Module::off();        
    }
}

void Attacker::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Attacker::loop()
{   
    // read bus
    senseBus();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case Attacker::eSTATE_SELECT:                        
            break;
            
        case Attacker::eSTATE_MOVE:
            break;

        case Attacker::eSTATE_DONE:                        
            break;
    }   // end switch    
    
    if (isStateChanged())
    {
        showStateName();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void Attacker::senseBus()
{
}

void Attacker::writeBus()
{
}

 // updates game action with best moves
void Attacker::updateGameAction()
{
    /*
    GameMove oAttackMove;
    GameMove oDefenseMove;
    
    // get best attack & defense moves from list moves
    LOG4CXX_INFO(logger, "possible moves ...");
    for (GameMove& oMove: listGameMoves) 
    {
        LOG4CXX_INFO(logger, oMove.shortDesc());
        if (oMove.getQattack() > oAttackMove.getQattack())
        {
            oAttackMove = oMove;
        }
        if (oMove.getQdefense() > oDefenseMove.getQdefense())
        {
            oDefenseMove = oMove;
        }
    }

    if (listGameMoves.size() > 0)
    {
        LOG4CXX_INFO(logger, "> best attack: " << oAttackMove.shortDesc());
        LOG4CXX_INFO(logger, "> best defense: " << oDefenseMove.shortDesc());
    }

    // update attack move if this is better
    if (oAttackMove.getQattack() > pGameAction->getAttackMoveReward())
    {
        LOG4CXX_INFO(logger, "new attack action !!!");
        pGameAction->updateAttackInfo(oAttackMove);
    }
    // track best defense
    if (oDefenseMove.getQdefense() > pGameAction->getDefenseMoveReward())
    {
        LOG4CXX_INFO(logger, "new defense action !!!");
        pGameAction->updateDefenseInfo(oDefenseMove);                        
    } 
     */       
}

// Shows the state name
void Attacker::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case Attacker::eSTATE_SELECT:
            stateName = "select";
            break;
            
        case Attacker::eSTATE_MOVE:
            stateName = "move";
            break;

        case Attacker::eSTATE_DONE:
            stateName = "done";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}