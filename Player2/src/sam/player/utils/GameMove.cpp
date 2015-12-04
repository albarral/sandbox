/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/GameMove.h"

namespace sam
{   
namespace player
{
GameMove::GameMove()
{
    Q = 0.0;
    element = 0;
}

void GameMove::update(BoardZone& oZone, int element, float Qvalue)
{
    this->oZone = oZone;
    this->element = element;   
    Q = Qvalue;
}

// gets GameMove description
std::string GameMove::toString()
{
  return ("GameMove: [zone = " + oZone.getID() +  
      ", element = " + std::to_string(element) + 
      ", Q = " + std::to_string(Q) + "]");     
}

}
}