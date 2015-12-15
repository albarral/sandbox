/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/Move.h"

namespace sam
{   
namespace player
{
Move::Move()
{
    type = Move::eMOVE_UNDEFINED;
}


void Move::setBoardPlace(BoardPlace& oBoardPlace)
{
    this->oBoardPlace = oBoardPlace;
}

std::string Move::getTypeName()
{
    std::string name;
    switch (type)
    {
        case Move::eMOVE_PICK:
            name = "pick";
            break;

        case Move::eMOVE_PLACE:
            name = "place";
            break;
            
        default:
            name = "undefined";
            break;            
    }
    return name;
}

// gets Move description
std::string Move::toString()
{
  return ("Move: [BoardPlace: " + oBoardPlace.toString() +  
      ", type = " + getTypeName() + "]");     
}

}
}