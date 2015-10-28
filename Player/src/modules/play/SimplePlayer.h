#ifndef __SAM_SIMPLE_PLAYER_H
#define __SAM_SIMPLE_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "modules/Player.h"
#include "learn/GameTask.h"
#include "modules/play/Strategy.h"

namespace sam 
{
// Simple version of the Player agent.
// Has no learning capability and uses a suboptimal prefixed strategy.
class SimplePlayer : public Player
{
private:
    Strategy oStrategy;         // defensive strategy 

public:
    SimplePlayer();
            
private:    
    // select a proper cell in the game board (using any strategy) and mark it
    virtual void chooseCell();
    // finish the game in a proper manner
    virtual void finishGame();

};
}
#endif
