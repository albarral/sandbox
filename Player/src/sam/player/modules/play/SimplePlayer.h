#ifndef __SAM_SIMPLE_PLAYER_H
#define __SAM_SIMPLE_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/Player.h"
#include "sam/player/learn/GameTask.h"
#include "sam/player/modules/play/Strategy.h"

namespace sam 
{
namespace player
{     
// Simple version of the Player agent.
// It's player purpose is of trainer type.
// Has no learning capability and uses a suboptimal prefixed strategy.
class SimplePlayer : public Player
{
private:
    Strategy oStrategy;         // defensive strategy 

public:
    SimplePlayer();
    ~SimplePlayer();
            
private:    
    // select a proper cell in the game board (using any strategy) and mark it
    virtual void chooseCell();
    // finish the game in a proper manner
    virtual void endOfGame();

};
}
}
#endif