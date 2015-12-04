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
    BoardZone oZone;    // board zone (a line) where the move is done
    int element;               // element (a cell) where the move is done
    float Q;                     // Q value (expected reward)
    
public:
    GameMove();
              
    void reset() {Q = -1.0;};
        
    BoardZone& getZone() {return oZone;}    
    int getElement() {return element;};   
    int getQ() {return Q;};
    
    void update(BoardZone& oZone, int element, float Qvalue);
};

}
}
#endif
