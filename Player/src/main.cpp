/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "GameManager.h"
#include "learn/GameTask.h"
#include "TaskFactory.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.player"));

void insertTaskInDatabase();
void testPlayer();

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");

//    insertTaskInDatabase();
    
    testPlayer();
    
    return 0;
}

// Creates the T3Task and inserts it in DB (to be USED just one TIME)
void insertTaskInDatabase()
{
    sam::GameTask oGameTask; 
    
    LOG4CXX_INFO(logger, "Creating game task ... (AND INSERTING IT FOR FIRST TIME IN DATABASE!!!)");     
    sam::TaskFactory::buildTicTacToeTask(oGameTask);
    
    oGameTask.storeInMemo();
    oGameTask.storeInMemo2();
}

void testPlayer()
{
    LOG4CXX_INFO(logger, "\n\n\n<<<<<<<<<<<<<<<< TEST PLAYER >>>>>>>>>>>>>>");
      
    sam::GameManager oGameManager; 
    oGameManager.startModules();
    
    LOG4CXX_INFO(logger, ">>>>>> New game:"); 
    
    while (oGameManager.isGameOver() == false)
        sleep(1);
    
    oGameManager.stopModules();
    sleep(2);
    
    //store Qs y update GameState y State
    
    LOG4CXX_INFO(logger, "End of test"); 
}
