/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/analyse/SimpleAnalyser2.h"
#include "sam/player/data/PlayerData.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr SimpleAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

SimpleAnalyser::SimpleAnalyser() 
{
    LOG4CXX_INFO(logger, "SimpleAnalyser created");         
}

void SimpleAnalyser::searchAttackMove(int playMode)
{
    // simple play mode
    if (playMode == PlayerData::eMODE_SIMPLE)
    {
        oStrategy.attack(numMines, numOthers, numEmpties, listEmptyCells);
    }
    // random play mode
    else if (playMode == PlayerData::eMODE_RANDOM)
    {
        oStrategy.moveRandom(listEmptyCells);
    }

    // set attack element & reward
    attackElement = oStrategy.getBestMove();        
    Qattack = oStrategy.getBestChance();              
    LOG4CXX_INFO(logger, "attack move: " << attackElement << ", Q=" << Qattack);  
}

void SimpleAnalyser::searchDefenseMove(int playMode)
{
    // no defensive moves performed
    Qdefense = -1.0;
    defenseElement = -1;
    LOG4CXX_INFO(logger, "no defense: Q=" << Qdefense);  
}

void SimpleAnalyser::storeKnowledge()
{
    LOG4CXX_INFO(logger, "no knowledge");         
}

}
}