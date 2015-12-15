#ifndef __SAM_PLAYER_BOARDPLACE_H
#define __SAM_PLAYER_BOARDPLACE_H

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
// Utility base class to represent a board place, an element of a board zone.
class BoardPlace
{
private:   
    BoardZone oBoardZone;    // board zone where the move is done
    int element;               // element or cell where the move is done
    
public:
    BoardPlace();
            
    BoardZone& getZone() {return oBoardZone;}    
    void setZone(BoardZone& oZone) {this->oBoardZone = oZone;};

    int getElement() {return element;};       
    void setElement(int element) {this->element = element;};
    
    // gets description
    std::string toString();
};

}
}
#endif
