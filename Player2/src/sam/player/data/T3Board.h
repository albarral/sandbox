#ifndef __SAM_PLAYER_T3BOARD_H
#define __SAM_PLAYER_T3BOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/Board.h"

namespace sam
{
namespace player
{    
// Class that represents a tic-tac-toe board
// It has 8 different BoardZones, each of them a T3Line.
// Derives from Board
class T3Board : public Board
{
public:
    T3Board();              
};

}
}
#endif
