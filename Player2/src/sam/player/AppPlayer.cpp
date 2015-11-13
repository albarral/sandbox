/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/AppPlayer.h"
#include "sam/player/modules/analyse/SimpleAnalyser.h"

namespace sam 
{
namespace player
{  
log4cxx::LoggerPtr AppPlayer::logger(log4cxx::Logger::getLogger("sam.player"));

AppPlayer::AppPlayer() 
{
    pLineAnalyser = 0;
    counter = 0;
}

AppPlayer::~AppPlayer() 
{
    if (pLineAnalyser != 0)
        delete (pLineAnalyser);
}

 // TEMP for test
void AppPlayer::setTestMarks()
{
    oPlayerMode.setEmptyMark(0);
    oPlayerMode.setMyMark(1);        
}

 // TEMP for test
void AppPlayer::setTestLine()
{
    int line111[3] = {oPlayerMode.getMyMark(), oPlayerMode.getMyMark(), oPlayerMode.getMyMark()};
    int line222[3] = {2, 2, 2};
    int line010[3] = {oPlayerMode.getEmptyMark(), oPlayerMode.getMyMark(), oPlayerMode.getEmptyMark()};
    int line221[3] = {2, 2, oPlayerMode.getMyMark()};
    
    int* pLine = 0;
    switch (counter)
    {
        case 1: 
            pLine = line111;
            break;
        case 2: 
            pLine = line222;
            break;
        case 3: 
            pLine = line010;
            break;
        case 4: 
            pLine = line221;
            break;
    }
    
    if (pLine != 0)
    {
        oBoardLine.setLineCell(BoardLine::eCELLS_FIRST, pLine[0]);
        oBoardLine.setLineCell(BoardLine::eCELLS_SECOND, pLine[1]);
        oBoardLine.setLineCell(BoardLine::eCELLS_THIRD, pLine[2]);        
    }
}

void AppPlayer::startModules()
{ 
    // game is started with 2 player agents (SAM & TAM) & first turn assigned randomly
    LOG4CXX_INFO(logger, "AppPlayer: starting modules ..."); 

    // TEMP for test
    setTestMarks();
    setTestLine();
    
    pLineAnalyser = new SimpleAnalyser();    
    pLineAnalyser->init(oBoardLine, oPlayerMode);
    //oLineAnalyser.connect(oBus);
    pLineAnalyser->setFrequency(4.0);
    pLineAnalyser->on();    
}

void AppPlayer::stopModules()
{
    // players are asked to stop, then we wait for them to finish
    LOG4CXX_INFO(logger, "AppPlayer: stopping modules ..."); 

    pLineAnalyser->off();
    pLineAnalyser->wait();
    
    LOG4CXX_INFO(logger, "AppPlayer: off");
}

bool AppPlayer::isGameOver()
{
    counter++;

    // TEMP for test    
    setTestLine();
    
    if (counter == 5)
        return true;
    else 
        return false;
}

}
}