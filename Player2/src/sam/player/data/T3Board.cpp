/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/data/T3Board.h"
#include "sam/player/utils/BoardZone.h"

namespace sam
{   
namespace player
{
T3Board::T3Board()
{
    // first the GAME zones of the tic-tac-toe board
    // 3 rows + 3 columns + 2 diagonals
   
    std::string lineID; // the zone ID 
    
    // add the 3 rows 
    BoardZone oRow;
    oRow.setNumElements(3);
    oRow.setType(T3Board::eZONE_ROW);    
    for (int i=0; i<3; i++)
    {
        lineID = "row " + std::to_string(i);
        oRow.setID(lineID);
        oRow.setOrdinal(i);
        addGameZone(oRow);                
    }
    
    // add the 3 columns 
    BoardZone oColumn;
    oColumn.setNumElements(3);
    oColumn.setType(T3Board::eZONE_COL);    
    for (int i=0; i<3; i++)
    {
        lineID = "column " + std::to_string(i);
        oColumn.setID(lineID);
        oColumn.setOrdinal(i);
        addGameZone(oColumn);                
    }
    
    // add the main diagonal 
    lineID = "main_diagonal";
    BoardZone oDiagonal;
    oDiagonal.setNumElements(3);
    oDiagonal.setType(T3Board::eZONE_MAIN_DIAGONAL);  
    oDiagonal.setID(lineID);
    oDiagonal.setOrdinal(0);
    addGameZone(oDiagonal);                

    // add the anti diagonal 
    lineID = "anti_diagonal";
    oDiagonal.setType(T3Board::eZONE_ANTI_DIAGONAL);  
    oDiagonal.setID(lineID);
    oDiagonal.setOrdinal(0);    // unchanged
    addGameZone(oDiagonal);                

    // then the EXTRA zones ...
    
    // extra zone (my home)
    BoardZone oMyHome;
    oMyHome.setID("myHome");
    oMyHome.setNumElements(1);
    oMyHome.setType(T3Board::eEXTRA_MY_HOME);    
    addExtraZone(oMyHome);

    // extra zone (rival's home)
    BoardZone oRivalHome;
    oRivalHome.setID("rivalHome");
    oRivalHome.setNumElements(1);
    oRivalHome.setType(T3Board::eEXTRA_RIVAL_HOME);    
    addExtraZone(oRivalHome);
}


}
}