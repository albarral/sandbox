#ifndef __SAM_PLAYER_BOARD_H
#define __SAM_PLAYER_BOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "sam/player/utils/BoardZone.h"

namespace sam
{
namespace player
{    
// Utility base class to represent a board (ie. a tic-tac-toe board)
class Board
{
private:   
    std::vector<BoardZone> listZones;      // list of zones in the board
    
public:
    Board();
              
    int getNumZones();
    void addZone(BoardZone& oBoardZone);
    
    // returns a list of zones of the specified type
    std::vector<BoardZone> getZonesOfType(int type);    
    // returns the zone in the specified position of the zones list
    BoardZone& getZone(int index);
    
    virtual std::vector<int> getZoneTypes() = 0;
};

}
}
#endif
