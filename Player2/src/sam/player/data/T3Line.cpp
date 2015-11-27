/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/T3Line.h"

namespace sam
{   
namespace player
{
T3Line::T3Line()
{
    numElements = 3;
}

std::vector<int> T3Line::getZoneTypes()
{
    std::vector<int> listTypes;
      
    listTypes.push_back(T3Line::eTYPE_ROW);
    listTypes.push_back(T3Line::eTYPE_COL);
    listTypes.push_back(T3Line::eTYPE_MAIN_DIAGONAL);
    listTypes.push_back(T3Line::eTYPE_ANTI_DIAGONAL);
    
    return listTypes;
}
}
}