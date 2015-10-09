#ifndef __SAM_UPDATEREWARDS_H
#define __SAM_UPDATEREWARDS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "learn/GameState.h"

namespace sam
{  
class UpdateRewards
{   
public:
    UpdateRewards();
    
    void computeDistances(GameState& oGameState);
    void computeRewards(GameState& oGameState);
};
}

#endif

