/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "GameManager.h"
#include "RewardCalculator.h"
#include "learn/GameTask.h"
#include "learn/GameDistance.h"

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
    sam::GameTask oGameTask; 
    
    LOG4CXX_INFO(logger, "*** INIT task"); 
    //Init task
    oGameTask.init(sam::GameTask::eTASK_TICTACTOE);
    
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
    
    //store Q y update State y Transition
    
    LOG4CXX_INFO(logger, "End of test"); 
}
