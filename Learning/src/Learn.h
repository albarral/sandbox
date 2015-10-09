#ifndef __SAM_LEARN_H
#define __SAM_LEARN_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "learn/GameState.h"

namespace sam
{
class Learn
{
private:   
    float gamma;
    
public:
    Learn();
    
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
