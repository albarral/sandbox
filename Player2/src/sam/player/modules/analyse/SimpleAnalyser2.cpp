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

void SimpleAnalyser::checkMoves4Attack(int playMode)
{    
    float Qattack;
    
    // skip if no moves available
    if (listMoves.size() == 0)
        return;
    
    // simple play mode
    if (playMode == PlayerData::eMODE_SIMPLE)
    {
        Qattack = oStrategy.attack(numMines, numOthers, numEmpties);        
    }
    // random play mode
    else if (playMode == PlayerData::eMODE_RANDOM)
    {
        Qattack = oStrategy.randomAttack();
    }
    // update the attack reward for all line moves
    for (GameMove& oMove: listMoves) 
    {
        oMove.setQattack(Qattack);
    }
    //LOG4CXX_INFO(logger, "Qattack (line) = " << Qattack);  
}

void SimpleAnalyser::checkMoves4Defense(int playMode)
{
    float Qdefense;

    // skip if no moves available
    if (listMoves.size() == 0)
        return;

    // simple play mode
    if (playMode == PlayerData::eMODE_SIMPLE)
    {
        Qdefense = oStrategy.defend(numMines, numOthers, numEmpties);
    }
    // random play mode
    else if (playMode == PlayerData::eMODE_RANDOM)
    {
        Qdefense = oStrategy.randomDefense();
    }

    // update the defense reward for all line moves
    for (GameMove& oMove: listMoves) 
    {
        oMove.setQdefense(Qdefense);
    }
    //LOG4CXX_INFO(logger, "Qdefense (line) = " << Qdefense);  
}

void SimpleAnalyser::storeKnowledge()
{
    LOG4CXX_INFO(logger, "no knowledge");         
}

}
}