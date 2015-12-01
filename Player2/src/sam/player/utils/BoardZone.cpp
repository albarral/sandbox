/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/BoardZone.h"

namespace sam
{   
namespace player
{
BoardZone::BoardZone()
{
    // initially the zone is invalid 
    ID = "";
    type = -1;
    ordinal = 0;
    numElements = 0;
}
}
}