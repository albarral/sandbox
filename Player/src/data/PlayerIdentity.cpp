/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "PlayerIdentity.h"

namespace sam
{   
PlayerIdentity::PlayerIdentity()
{
    ID = "";
    myMark = 0;
    bExplorationMode = false;
    setPlayMode(eMODE_SIMPLE);
}

void PlayerIdentity::setPlayMode(int playMode)
{
    // just set if valid value
    if (playMode >= 0 && playMode <= eMODE_SMART)
        this->playMode = playMode;
}

std::string PlayerIdentity::toString()
{
  return ("PlayerIdentity: [ID = " + ID +
          ", myMark = " + std::to_string(myMark) + 
          ", playMode = " + std::to_string(playMode) + "]");  
}
}
