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
    // all game moves are of place type
    type = Move::eMOVE_PLACE;
    reset();
}

void GameMove::reset()
{
    Qattack = -1.0;
    Qdefense = -1.0;
}

// get full description
std::string GameMove::toString()
{
  return ("GameMove: [" + oBoardPlace.toString() +  
      ", Qattack = " + std::to_string(Qattack) + 
      ", Qdefense = " + std::to_string(Qdefense) + 
          "]");     
}

// get short description
std::string GameMove::shortDesc()
{
  return (oBoardPlace.shortDesc() +  
      ", Qattack = " + std::to_string(Qattack) + 
      ", Qdefense = " + std::to_string(Qdefense));     
}

}
}