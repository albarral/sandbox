#ifndef __SAM_GAME_MANAGER_H
#define __SAM_GAME_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "data/GameBoard.h"
#include "modules/Player.h"

namespace sam 
{
class GameManager
{
private:
    static log4cxx::LoggerPtr logger;
    GameBoard oBoard;
    Player oSam;
    Player oTam;
    
public:
    GameManager();
    
    void startModules();
    void stopModules();
    bool isGameOver();
  
};
}

#endif
