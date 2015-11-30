/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/T3Board.h"
#include "sam/player/utils/BoardZone.h"

namespace sam
{   
namespace player
{
T3Board::T3Board()
{
    // defines the list of zones of the tic-tac-toe board
    // 3 rows + 3 columns + 2 diagonals
   
    int lineID; // the zone ID 
    
    // add the 3 rows (IDs 0-2)
    BoardZone oRow;
    oRow.setNumElements(3);
    oRow.setType(T3Board::eTYPE_ROW);    
    lineID = 0;
    for (int i=0; i<3; i++)
    {
        oRow.setID(lineID);
        this->addZone(oRow);                
        lineID ++;
    }
    
    // add the 3 columns (IDs 3-5)
    BoardZone oColumn;
    oColumn.setNumElements(3);
    oColumn.setType(T3Board::eTYPE_COL);    
    for (int i=0; i<3; i++)
    {
        oColumn.setID(lineID);
        this->addZone(oColumn);                
        lineID ++;
    }
    
    // add the main diagonal (ID 6)
    BoardZone oDiagonal;
    oDiagonal.setNumElements(3);
    oDiagonal.setType(T3Board::eTYPE_MAIN_DIAGONAL);  
    oDiagonal.setID(lineID);
    this->addZone(oDiagonal);                
    lineID ++;

    // add the anti diagonal (ID 7)
    oDiagonal.setType(T3Board::eTYPE_ANTI_DIAGONAL);  
    oDiagonal.setID(lineID);
    this->addZone(oDiagonal);                
}

std::vector<int> T3Board::getZoneTypes()
{
    std::vector<int> listTypes;
      
    listTypes.push_back(T3Board::eTYPE_ROW);
    listTypes.push_back(T3Board::eTYPE_COL);
    listTypes.push_back(T3Board::eTYPE_MAIN_DIAGONAL);
    listTypes.push_back(T3Board::eTYPE_ANTI_DIAGONAL);
    
    return listTypes;
}

}
}