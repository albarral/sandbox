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
    // game zone types
    enum eGameZones 
    {
        eZONE_ROW,
        eZONE_COL,  
        eZONE_MAIN_DIAGONAL,    // diagonal going from top-left to bottom-right        
        eZONE_ANTI_DIAGONAL,    // diagonal going from bottom-left to top-right
        eZONE_DIM  
    };
    // extra zone types
    enum eExtraZones 
    {
        eEXTRA_MY_HOME,             // my home zone (place for my unused pieces)
        eEXTRA_RIVAL_HOME,          // rival's home zone (place for rival's unused pieces) 
        eEXTRA_DIM                       // dimension of eLine enum
    };
        
    T3Board();            
};

}
}
#endif
