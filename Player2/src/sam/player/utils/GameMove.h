#ifndef __SAM_PLAYER_GAMEMOVE_H
#define __SAM_PLAYER_GAMEMOVE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/BoardZone.h"

namespace sam
{
namespace player
{    
// Utility base class to represent a game move (a board zone, an element of the zone and an associated reward)
class GameMove
{
private:   
    float Q;                     // Q value (expected reward)
    BoardZone oZone;    // board zone where the move is done
    int element;               // element (in the zone) where the move is done
    
public:
    GameMove();
              
    void setQ(float value) {Q = value;};
    int getQ() {return Q;};
    
    void setZone(BoardZone& oZone) {this->oZone = oZone;};
    BoardZone& getZone() {return oZone;}
    
    void setElement(int value) {element = value;};    
    int getElement() {return element;};    
};

}
}
#endif
