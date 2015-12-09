#ifndef __SAM_PLAYER_GAMEMOVE_H
#define __SAM_PLAYER_GAMEMOVE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

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
    float Qattack;                     // Q value (expected reward)
    float Qdefense;                     // Q value (expected reward)
    
public:
    GameMove();
    GameMove(BoardZone& oZone);
    
    void reset();
        
    BoardZone& getZone() {return oZone;}    
    int getElement() {return element;};   
    float getQattack() {return Qattack;};
    float getQdefense() {return Qdefense;};
    
    void update(BoardZone& oZone, int element, float Qattack, float Qdefense);

    void setElement(int element) {this->element = element;};
    void setQattack(float Qvalue) {Qattack = Qvalue;};
    void setQdefense(float Qvalue) {Qdefense = Qvalue;};
    
    // gets GameMove description
    std::string toString();
};

}
}
#endif
