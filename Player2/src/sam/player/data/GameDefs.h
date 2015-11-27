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
        eCELLS_FIRST, 
        eCELLS_SECOND,
        eCELLS_THIRD,
        eCELLS_DIM
    };
    // line types
    enum eType 
    {
        eTYPE_ROW1,
        eTYPE_ROW2,
        eTYPE_ROW3,
        eTYPE_COL1,  
        eTYPE_COL2,
        eTYPE_COL3,
        eTYPE_DIAG1,
        eTYPE_DIAG2,
        eTYPE_DIM   // dimension of eLine enum
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
