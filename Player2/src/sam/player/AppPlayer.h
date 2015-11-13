#ifndef __SAM_APP_PLAYER_H
#define __SAM_APP_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/bus/Bus.h"
#include "sam/player/data/BoardLine.h"
#include "sam/player/data/PlayerMode.h"
#include "sam/player/modules/analyse/LineAnalyser.h"

namespace sam 
{
namespace player
{  
class AppPlayer
{
private:
    static log4cxx::LoggerPtr logger;
    Bus oBus;
    BoardLine oBoardLine;
    PlayerMode oPlayerMode;
    LineAnalyser* pLineAnalyser;
    // temp
    int counter = 0;
    
public:
    AppPlayer();
    ~AppPlayer();
        
    void startModules();
    void stopModules();
    bool isGameOver();
  
private:
    void setTestMarks(); // TMP for test
    void setTestLine(); // TMP for test
};
}
}

#endif
