#ifndef __SAM_LEARNPLAYER_H
#define __SAM_LEARNPLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "GameState.h"

namespace sam
{
class LearnPlayer
{
private:   
    float gamma;
    
public:
    LearnPlayer();
    
    float getGamma() {return gamma;};
    void setGamma(float value) {gamma = value;};

    // Compute the Q value from a state with one connection
    float computeQAttack(GameState& oGameState);
    float computeQDefend(GameState& oGameState);
   
private:    
    float maxQAttackValue(GameState& oGameState);
    float maxQDefendValue(GameState& oGameState);
};

}

#endif
