/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/BoardZone.h"

namespace sam
{   
namespace player
{
BoardZone::BoardZone()
{
    // initially the zone is invalid 
    ID = "";
    type = -1;
    ordinal = 0;
    numElements = 0;
}

// gets description
std::string BoardZone::toString()
{
  return ("BoardZone: [ID = " + ID +  
      ", type = " + std::to_string(type) + 
      ", ordinal = " + std::to_string(ordinal) + 
      ", numElements = " + std::to_string(numElements) + 
          "]");     
}

}
}