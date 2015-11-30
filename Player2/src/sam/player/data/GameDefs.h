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
    // result of line analysis
    enum eResult  
    {
        eRESULT_OPEN,        // open line (some empty cell)
        eRESULT_CLOSED,    // closed line (filled line, no winner)
        eRESULT_WON,        // winner line (3 mines)
        eRESULT_LOST,       // lost line (3 other's)
        eRESULT_DIM
    };
    // cell values
    enum eMark  
    {
        eMARK_EMPTY,        // empty cell
        eMARK_MINE,          // cell with my mark
        eMARK_OTHER       // cell with other's mark
    };
    
    static const int INVALID_VALUE = -1;
};

}
}
#endif
