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
// Utility base class to represent a board.
// It has board zones for playing (game zones) and extra zones for other purposes (like storing unused pieces)
class Board
{
private:   
    std::vector<BoardZone> listGameZones;      // list of game zones (for playing)
    std::vector<BoardZone> listExtraZones;      // list of extra zones (for other purposes)
    
public:
    Board();
              
    int getNumGameZones() {return listGameZones.size();};
    // add zone to list of game zones
    void addGameZone(BoardZone& oBoardZone);

    int getNumExtraZones() {return listExtraZones.size();};
    // add zone to list of extra zones
    void addExtraZone(BoardZone& oBoardZone);
    
    // returns a list of all game zones in the board
    std::vector<BoardZone>& getListGameZones() {return listGameZones;};    
    // returns a list of all extra zones in the board
    std::vector<BoardZone>& getListExtraZones() {return listExtraZones;};    

    // returns a list of zones of the specified type
    std::vector<BoardZone> getGameZonesOfType(int type);    
       
};

}
}
#endif
