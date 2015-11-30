/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/Board.h"

namespace sam
{   
namespace player
{
Board::Board()
{
}

int Board::getNumZones()
{
    return listZones.size();
}

void Board::addZone(BoardZone& oBoardZone)
{
    listZones.push_back(oBoardZone);
}

std::vector<BoardZone> Board::getZonesOfType(int type)
{
    std::vector<BoardZone> listSpecificZones;
    
    // walk zones list and extract those of the specified type
    for (BoardZone& oZone: listZones) 
    {
        if (oZone.getType() == type)
            listSpecificZones.push_back(oZone);
    }

    return listSpecificZones;
}

BoardZone& Board::getZone(int index)
{
    return listZones.at(index);
}


}
}