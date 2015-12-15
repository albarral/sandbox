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

void Board::addGameZone(BoardZone& oBoardZone)
{
    listGameZones.push_back(oBoardZone);
}

void Board::addExtraZone(BoardZone& oBoardZone)
{
    listExtraZones.push_back(oBoardZone);
}

std::vector<BoardZone> Board::getGameZonesOfType(int type)
{
    std::vector<BoardZone> listSpecificZones;
    
    // walk zones list and extract those of the specified type
    for (BoardZone& oZone: listGameZones) 
    {
        if (oZone.getType() == type)
            listSpecificZones.push_back(oZone);
    }

    return listSpecificZones;
}


}
}