/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/player/GameManager.h"
#include "sam/player/learn/GameTask.h"
#include "sam/player/TaskFactory.h"
#include "sam/player/modules/BoardSensor.h"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.player"));

void insertTaskInDatabase();
void testPlayer();
void testBoardSensor();

using namespace sam;

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
//    insertTaskInDatabase();
  
    testPlayer();
    //testBoardSensor();
    
    return 0;
}

// Creates the T3Task and inserts it in DB (to be USED just one TIME)
void insertTaskInDatabase()
{ 
    player::GameTask oGameTask;
    
    LOG4CXX_INFO(logger, "Creating game task ... (AND INSERTING IT FOR FIRST TIME IN DATABASE!!!)");     
    player::TaskFactory::buildTicTacToeTask(oGameTask);
    
    oGameTask.storeInMemo2();
}

void testPlayer()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST PLAYER >>>>>>>>>>>>>>\n");
      
    player::GameManager oGameManager; 
    // setGameTask   SAM vs TAM   or    SAM vs HUMAN
    oGameManager.setGameType(player::GameManager::eGAME_SAM_VS_TAM);
    oGameManager.startModules();
    
    LOG4CXX_INFO(logger, ">>>>>> New game:"); 
    
    while (oGameManager.isGameOver() == false)
        sleep(1);
    
    oGameManager.stopModules();
    sleep(2);
    
    LOG4CXX_INFO(logger, "End of test"); 
}


void testBoardSensor()
{
    LOG4CXX_INFO(logger, "\n\n\n<<<<<<<<<<<<<<<< TEST BOARD SENSOR >>>>>>>>>>>>>>");
    player::BoardSensor oBoardSensor;    
    player::GameBoard oGameBoard;
    
    for (int i=0; i<10; i++)
    {
        oBoardSensor.senseBoard(oGameBoard);

        LOG4CXX_INFO(logger, i << "\n " << oGameBoard.getMatrix());
        LOG4CXX_INFO(logger, "ID:" << oBoardSensor.getLastMoveNumber());
        LOG4CXX_INFO(logger, "player: " << oBoardSensor.getLastMovePlayer());
        LOG4CXX_INFO(logger, "status: " << oBoardSensor.getLastMoveStatus());
        
         sleep(2);
    }
    
}