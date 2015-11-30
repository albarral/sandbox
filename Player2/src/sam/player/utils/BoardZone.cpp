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
    ID = -1;
    type = -1;
    numElements = 0;
}

std::vector<int> BoardZone::getZoneTypes()
{
    std::vector<int> listTypes;
    // return empty list
    return listTypes;
}
}
}