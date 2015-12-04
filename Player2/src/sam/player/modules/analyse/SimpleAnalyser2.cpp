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
        oStrategy.randomAttack(listEmptyCells);
    }

    // set attack element & reward
    attackElement = oStrategy.getAttackElement();        
    Qattack = oStrategy.getAttackChance();              
    LOG4CXX_INFO(logger, "attack move: " << attackElement << ", Q=" << Qattack);  
}

void SimpleAnalyser::searchDefenseMove(int playMode)
{
    // simple play mode
    if (playMode == PlayerData::eMODE_SIMPLE)
    {
        oStrategy.defend(numMines, numOthers, numEmpties, listEmptyCells);
    }
    // random play mode
    else if (playMode == PlayerData::eMODE_RANDOM)
    {
        oStrategy.randomDefense(listEmptyCells);
    }

    // set defense element & reward
    defenseElement = oStrategy.getDefenseElement();
    Qdefense = oStrategy.getDefenseChance();
    LOG4CXX_INFO(logger, "defense move: " << defenseElement << ", Q=" << Qdefense);  
}

void SimpleAnalyser::storeKnowledge()
{
    LOG4CXX_INFO(logger, "no knowledge");         
}

}
}