/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/player/AppPlayer.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.player"));

void insertTaskInDatabase();
void testPlayer();
void testBoardSensor();

using namespace sam;

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testPlayer();
    
    return 0;
}

void testPlayer()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST PLAYER2  >>>>>>>>>>>>>>\n");
      
    player::AppPlayer oAppPlayer; 
    oAppPlayer.startModules();
        
    while (oAppPlayer.isGameOver() == false)
        sleep(1);
    
    oAppPlayer.stopModules();
    sleep(2);
    
    LOG4CXX_INFO(logger, "End of test"); 
}

