/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/AppPlayer.h"
#include "sam/player/modules/watch/VirtualWatcher.h"
#include "sam/player/modules/move/VirtualMover.h"
#include "modules/analyse/GameAnalyser.h"

namespace sam 
{
namespace player
{  
log4cxx::LoggerPtr AppPlayer::logger(log4cxx::Logger::getLogger("sam.player"));

AppPlayer::AppPlayer() 
{
    counter = 0;
    pGameBoard = 0;
    pBoardWatcher = 0;
}

AppPlayer::~AppPlayer() 
{
    if (pBoardWatcher != 0)
        delete (pBoardWatcher);
    if (pGameBoard != 0)
        delete (pGameBoard);
}

 // TEMP for test
void AppPlayer::emptyBoard()
{
    LOG4CXX_INFO(logger, "Empty board"); 
    
    VirtualMover oVirtualMover;
    
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
        oVirtualMover.removePiece(i, j);
}


void AppPlayer::startModules()
{ 
    // game is started with 2 player agents (SAM & TAM) & first turn assigned randomly
    LOG4CXX_INFO(logger, "AppPlayer: starting modules ..."); 

    // TEMP for test
//    oPlayerMode.setEmptyMark(0);
//    oPlayerMode.setMyMark(1);        
    emptyBoard();
    
    pGameBoard = new GameBoard(3);
    
    pBoardWatcher = new VirtualWatcher();
    pBoardWatcher->init(*pGameBoard);
    pBoardWatcher->connect(oBus);
    pBoardWatcher->setFrequency(4.0);
    pBoardWatcher->on();      
    
    oGameAnalyser.init(*pGameBoard, oGameAction);
    oGameAnalyser.connect(oBus);
    oGameAnalyser.setFrequency(4.0);
    oGameAnalyser.on();
}

void AppPlayer::stopModules()
{
    // players are asked to stop, then we wait for them to finish
    LOG4CXX_INFO(logger, "AppPlayer: stopping modules ..."); 

    oGameAnalyser.off();
    oGameAnalyser.wait();
    
    pBoardWatcher->off();
    pBoardWatcher->wait();
        
    LOG4CXX_INFO(logger, "AppPlayer: off");
}

bool AppPlayer::isGameOver()
{
    counter++;

    if (counter == 10)
        return true;
    else 
        return false;
}

}
}