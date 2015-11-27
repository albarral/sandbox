/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/player/AppPlayer.h"
#include "sam/player/ConsolePlayer.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.player"));

using namespace sam;

void insertTaskInDatabase();
void testPlayer();

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
    player::ConsolePlayer oConsolePlayer;
//    oAppPlayer.startModules();
        
    while (!oAppPlayer.isGameOver() && !oConsolePlayer.want2QuitGame())
    {
        oConsolePlayer.play();
        sleep(1);
    }
    
//    oAppPlayer.stopModules();
    sleep(2);
    
    LOG4CXX_INFO(logger, "End of test"); 
}
    
