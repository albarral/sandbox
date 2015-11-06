#ifndef __SAM_GAME_MANAGER_H
#define __SAM_GAME_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/data/GameBoard.h"
#include "sam/player/data/GameFlow.h"
#include "sam/player/modules/Player.h"

namespace sam 
{
namespace player
{  
class GameManager
{
public:    
    enum eGameType
    {
        eGAME_SAM_VS_TAM,
        eGAME_SAM_VS_HUMAN
    };

private:
    static log4cxx::LoggerPtr logger;
    int gameType;
    GameBoard oGameBoard;
    GameFlow oGameFlow;
    Player* oSam;
    Player* oTam;
    
public:
    GameManager();
    ~GameManager();
    
    void setGameType(int type) {gameType = type;};
    
    void startModules();
    void stopModules();
    bool isGameOver();
  
};
}
}

#endif
