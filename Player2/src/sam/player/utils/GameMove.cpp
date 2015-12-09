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
    reset();
}

GameMove::GameMove(BoardZone& oZone)
{
    this->oZone = oZone;
    reset();
}

void GameMove::reset()
{
    element = -1;
    Qattack = -1.0;
    Qdefense = -1.0;
}

void GameMove::update(BoardZone& oZone, int element, float Qattack, float Qdefense)
{
    this->oZone = oZone;
    this->element = element;   
    this->Qattack = Qattack;
    this->Qdefense = Qdefense;
}

// gets GameMove description
std::string GameMove::toString()
{
  return ("GameMove: [zone = " + oZone.getID() +  
      ", element = " + std::to_string(element) + 
      ", Qattack = " + std::to_string(Qattack) + 
      ", Qdefense = " + std::to_string(Qdefense) + 
          "]");     
}

}
}