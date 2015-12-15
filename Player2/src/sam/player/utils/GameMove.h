#ifndef __SAM_PLAYER_GAMEMOVE_H
#define __SAM_PLAYER_GAMEMOVE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/utils/Move.h"

namespace sam
{
namespace player
{    
// Utility class to represent a game move.
// A GameMove is always a place Move, but with associated rewards for attack and defense game tasks.
class GameMove: public Move
{
private:   
    float Qattack;                     // Q value (expected reward)
    float Qdefense;                     // Q value (expected reward)
    
public:
    GameMove();

    void reset();
            
    float getQattack() {return Qattack;};
    void setQattack(float Qvalue) {Qattack = Qvalue;};

    float getQdefense() {return Qdefense;};
    void setQdefense(float Qvalue) {Qdefense = Qvalue;};
    
    // gets GameMove description
    virtual std::string toString();
};

}
}
#endif
