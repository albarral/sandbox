/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/GamePiece.h"

namespace sam
{   
namespace player
{
GamePiece::GamePiece()
{
    // initially the zone is invalid 
    ID = "";
    type = -1;
    team = 0;
    numInstances = 0;
}

// gets description
std::string GamePiece::toString()
{
  return ("GamePiece: [ID = " + ID +  
      ", type = " + std::to_string(type) + 
      ", team = " + std::to_string(team) + 
      ", numInstances = " + std::to_string(numInstances) + 
          "]");     
}

}
}