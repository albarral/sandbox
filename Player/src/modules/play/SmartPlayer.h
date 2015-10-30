#ifndef __SAM_SMART_PLAYER_H
#define __SAM_SMART_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "modules/Player.h"
#include "learn/GameTask.h"
#include "modules/play/Strategy2.h"

namespace sam 
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
#endif
