/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/BoardPlace.h"

namespace sam
{   
namespace player
{
BoardPlace::BoardPlace()
{
    element = -1;
}

// get full description
std::string BoardPlace::toString()
{
  return ("BoardPlace: [" + oBoardZone.toString() +  
      ", element = " + std::to_string(element) + 
          "]");     
}

// get short description
std::string BoardPlace::shortDesc()
{
  return ("[" + oBoardZone.getID() +  
      ", element = " + std::to_string(element) + 
          "]");     
}

}
}