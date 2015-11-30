#ifndef __SAM_APP_PLAYER_H
#define __SAM_APP_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/bus/Bus.h"
#include "sam/player/data/GameBoard.h"
#include "sam/player/data/GameAction.h"
//#include "sam/player/data/PlayerMode.h"
#include "sam/player/modules/watch/BoardWatcher.h"
#include "sam/player/modules/analyse/GameAnalyser.h"

namespace sam 
{
namespace player
{  
class AppPlayer
{
private:
    static log4cxx::LoggerPtr logger;
    Bus oBus;
    // shared data
    GameBoard* pGameBoard;
    GameAction oGameAction;
    //PlayerMode oPlayerMode;
    // modules
    BoardWatcher* pBoardWatcher;
    GameAnalyser oGameAnalyser;
    // temp
    int counter = 0;
    
public:
    AppPlayer();
    ~AppPlayer();
        
    void startModules();
    void stopModules();
    bool isGameOver();
  
private:
    void emptyBoard(); // TMP for test
};
}
}

#endif
