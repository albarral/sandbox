#ifndef __SAM_PLAYER_T3LINE_H
#define __SAM_PLAYER_T3LINE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/BoardZone.h"

namespace sam
{
namespace player
{    
// Class that represents a line of a tic-tac-toe board
// Derives from BoardZone
// Used in T3Board class    
class T3Line : public BoardZone
{
public:
    // line types
    enum eType 
    {
        eTYPE_ROW,
        eTYPE_COL,  
        eTYPE_MAIN_DIAGONAL,    // diagonal going from top-left to bottom-right
        eTYPE_ANTI_DIAGONAL,    // diagonal going from bottom-left to top-right
        eTYPE_DIM   // dimension of eLine enum
    };

    T3Line();

    virtual std::vector<int> getZoneTypes();
};

}
}
#endif
