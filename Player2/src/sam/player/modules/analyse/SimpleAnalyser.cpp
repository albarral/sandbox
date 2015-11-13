/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/analyse/SimpleAnalyser.h"
#include "sam/player/data/PlayerMode.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr SimpleAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

SimpleAnalyser::SimpleAnalyser() 
{
}

void SimpleAnalyser::searchBestAttack()
{
    // simple play mode
    if (pPlayerMode->getPlayMode() == PlayerMode::eMODE_SIMPLE)
    {
        oStrategy.attack(numMines, numOthers, numEmpties, listEmptyCells);
    }
    // random play mode
    else if (pPlayerMode->getPlayMode() == PlayerMode::eMODE_RANDOM)
    {
        oStrategy.attackRandom(listEmptyCells);
    }

    pBoardLine->setBestAttackCell(oStrategy.getBestMove());
    pBoardLine->setBestAttackQ(oStrategy.getBestChance());
    
    LOG4CXX_INFO(logger, "best attack: " << oStrategy.getBestMove() << ", Q=" << oStrategy.getBestChance());  
}

void SimpleAnalyser::searchBestDefense()
{
    // no defensive moves performed
    pBoardLine->setBestDefenseCell(BoardLine::INVALID_VALUE);
    pBoardLine->setBestDefenseQ(0.0);    

    LOG4CXX_INFO(logger, "best defense: " << BoardLine::INVALID_VALUE << ", Q=" << 0.0);  
}

void SimpleAnalyser::storeKnowledge()
{
    // nothing to do 
}

}
}