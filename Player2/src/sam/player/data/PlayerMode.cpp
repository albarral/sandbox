/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/PlayerMode.h"

namespace sam
{   
namespace player
{    
PlayerMode::PlayerMode()
{
    myMark = -1;
    emptyMark = 0;
    setPlayMode(eMODE_SIMPLE);
}

void PlayerMode::setPlayMode(int playMode)
{
    // just set if valid value
    if (playMode >= 0 && playMode < eMODE_DIM)
        this->playMode = playMode;
}

std::string PlayerMode::toString()
{
  return ("PlayerMode: [playMode = " + std::to_string(playMode) +  
          ", myMark = " + std::to_string(myMark) + 
          ", emptyMark = " + std::to_string(emptyMark) + "]");  
}

}
}