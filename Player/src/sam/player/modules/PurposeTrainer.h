#ifndef __SAM_PLAYER_TRAINERPURPOSE_H
#define __SAM_PLAYER_TRAINERPURPOSE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/PlayerPurpose.h"

namespace sam
{
namespace player
{    
// Class that manages the purpose of a TRAINER player type.
// The trainer player always plays in SIMPLE mode. 
// And as a good trainer he's always willing to play ;).
class PurposeTrainer : public PlayerPurpose
{
public:
    PurposeTrainer();
    
    // resets purpose
    virtual void reset();
    // evolves purpose
    virtual void evolve();
    // checks if agent wants to play a new game
    virtual bool want2PlayMore();
};

}
}
#endif
