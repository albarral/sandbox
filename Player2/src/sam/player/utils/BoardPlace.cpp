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

// gets description
std::string BoardPlace::toString()
{
  return ("BoardPlace: [" + oBoardZone.toString() +  
      ", element = " + std::to_string(element) + 
          "]");     
}

}
}