#ifndef __SAM_PLAYER_MOVE_H
#define __SAM_PLAYER_MOVE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/utils/BoardPlace.h"

namespace sam
{
namespace player
{    
// Utility base class to represent a move 
class Move
{
public:
    // movement types
    enum eTypes 
    {
        eMOVE_UNDEFINED,
        eMOVE_PICK,             // pick an object   
        eMOVE_PLACE          // place an object  
    };

protected:   
    BoardPlace oBoardPlace;    // board zone (a line) where the move is done
    int type;                   // movement type (pick or place)
    
public:
    Move();
          
    BoardPlace& getBoardPlace() {return oBoardPlace;}        
    void setBoardPlace(BoardPlace& oZone);

    int getType() {return type;};   
    void setType(int type) {this->type = type;};

    // gets the name of the type
    std::string getTypeName();    
    // gets Move description
    virtual std::string toString();
};

}
}
#endif
