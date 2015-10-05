/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "GameManager.h"
#include "RewardCalculator.h"
#include "modules/GameDistance.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.player"));

void initialize();
void testPlayer();

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");

    initialize();
    testPlayer();
    
    return 0;
}

void initialize()
{
    sam::RewardCalculator oRewardCalculator;
    oRewardCalculator.setKAttack(100);
    oRewardCalculator.setKDefend(100);
//    oRewardCalculator.setDMaxVictory(sam::GameDistance.computeDistance2Victory(0,3));
//    oRewardCalculator.setDMaxDefeat(sam::GameDistance.computeDistance2Defeat(3,0));
}

void testPlayer()
{
    LOG4CXX_INFO(logger, "<<<<<<<<<<<<<<<< TEST PLAYER >>>>>>>>>>>>>>");
      
    sam::GameManager oGameManager; 
    oGameManager.startModules();
    
    LOG4CXX_INFO(logger, ">>>>>> New game:"); 
    
    while (oGameManager.isGameOver() == false)
        sleep(1);
    
    oGameManager.stopModules();
    sleep(2);
    
    LOG4CXX_INFO(logger, "End of test"); 
}
