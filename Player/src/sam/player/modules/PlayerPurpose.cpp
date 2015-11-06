/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/PlayerPurpose.h"

namespace sam
{   
namespace player
{    
PlayerPurpose::PlayerPurpose()
{
    playerType = eTYPE_UNKNOWN;
    playMode = eMODE_UNKNOWN;
    gamesPlayed = 0;
}
}
}