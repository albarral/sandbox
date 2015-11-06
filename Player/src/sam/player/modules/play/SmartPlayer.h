#ifndef __SAM_SMART_PLAYER_H
#define __SAM_SMART_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/Player.h"
#include "sam/player/modules/play/Strategy2.h"
#include "sam/player/learn/GameTask.h"
#include "sam/player/utils/QExtractor.h"

namespace sam 
{
namespace player
{     
// Smart version of the Player agent.
// It's player purpose is of winner type.
// Uses Q-learning to improve its game knowledge.
// Manages attack and defense as different competing tasks.
class SmartPlayer : public Player
{
private:
    GameTask oAttackTask;            // ofensive task
    GameTask oDefenseTask;        // defensive task  
    Strategy2 oAttackStrategy;            // ofensive strategy
    Strategy2 oDefenseStrategy;         // defensive strategy 
    QExtractor oQExtractor;             // utility for Q monitoring

public:
    SmartPlayer();
    ~SmartPlayer();

    // initializes the module 
    virtual void init (std::string firstPlayerID);
        
private:    
    // select a proper cell in the game board (using any strategy) and mark it
    virtual void chooseCell();
    // finish the game in a proper manner
    virtual void endOfGame();

};
}
}
#endif
