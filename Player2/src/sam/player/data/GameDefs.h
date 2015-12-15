#ifndef __SAM_PLAYER_GAMEDEFS_H
#define __SAM_PLAYER_GAMEDEFS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam
{
namespace player
{    
// auxiliary class of project constants
class GameDefs
{   
public:
    // cell positions
    enum eCell
    {
        eCELL_FIRST, 
        eCELL_SECOND,
        eCELL_THIRD,
        eCELL_DIM
    };
    
    static const int INVALID_VALUE = -1;
};

}
}
#endif
