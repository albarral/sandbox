/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/T3Board.h"
#include "sam/player/data/T3Line.h"

namespace sam
{   
namespace player
{
T3Board::T3Board()
{
    // defines the list of zones of the tic-tac-toe board
    // 3 rows + 3 columns + 2 diagonals
   
    int lineID; // the zone ID 
    
    // add the 3 rows
    T3Line oRow;
    oRow.setType(T3Line::eTYPE_ROW);    
    lineID = 0;
    for (int i=0; i<3; i++)
    {
        oRow.setID(lineID);
        this->addZone(oRow);                
        lineID ++;
    }
    
    // add the 3 columns
    T3Line oColumn;
    oColumn.setType(T3Line::eTYPE_COL);    
    for (int i=0; i<3; i++)
    {
        oColumn.setID(lineID);
        this->addZone(oColumn);                
        lineID ++;
    }
    
    // add the main diagonal
    T3Line oDiagonal;
    oDiagonal.setType(T3Line::eTYPE_MAIN_DIAGONAL);  
    oDiagonal.setID(lineID);
    this->addZone(oDiagonal);                
    lineID ++;

    // add the anti diagonal
    oDiagonal.setType(T3Line::eTYPE_ANTI_DIAGONAL);  
    oDiagonal.setID(lineID);
    this->addZone(oDiagonal);                
}
  
}
}