/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/PlayerIdentity.h"

namespace sam
{   
namespace player
{    
PlayerIdentity::PlayerIdentity()
{
    ID = "";
    myMark = 0;
    setPlayMode(eMODE_SIMPLE);
}

void PlayerIdentity::setPlayMode(int playMode)
{
    // just set if valid value
    if (playMode >= 0 && playMode < eMODE_DIM)
        this->playMode = playMode;
}

std::string PlayerIdentity::toString()
{
  return ("PlayerIdentity: [ID = " + ID +
          ", myMark = " + std::to_string(myMark) + 
          ", playMode = " + std::to_string(playMode) + "]");  
}

}
}