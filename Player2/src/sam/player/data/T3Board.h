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
// It has 8 different BoardZones: 3 rows, 3 columns and 2 diagonals
// Derives from Board
class T3Board : public Board
{
public:
    // zone types
    enum eZones 
    {
        eTYPE_ROW,
        eTYPE_COL,  
        eTYPE_MAIN_DIAGONAL,    // diagonal going from top-left to bottom-right
        eTYPE_ANTI_DIAGONAL,    // diagonal going from bottom-left to top-right
        eTYPE_DIM   // dimension of eLine enum
    };

    T3Board();        
    
    virtual std::vector<int> getZoneTypes();
};

}
}
#endif
