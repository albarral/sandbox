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
    // defines the list of zones of the tic-tac-toe board
    // 3 rows + 3 columns + 2 diagonals
   
    std::string lineID; // the zone ID 
    
    // add the 3 rows 
    BoardZone oRow;
    oRow.setNumElements(3);
    oRow.setType(T3Board::eTYPE_ROW);    
    for (int i=0; i<3; i++)
    {
        lineID = "row " + std::to_string(i);
        oRow.setID(lineID);
        oRow.setOrdinal(i);
        this->addZone(oRow);                
    }
    
    // add the 3 columns 
    BoardZone oColumn;
    oColumn.setNumElements(3);
    oColumn.setType(T3Board::eTYPE_COL);    
    for (int i=0; i<3; i++)
    {
        lineID = "column " + std::to_string(i);
        oColumn.setID(lineID);
        oColumn.setOrdinal(i);
        this->addZone(oColumn);                
    }
    
    // add the main diagonal 
    lineID = "main_diagonal";
    BoardZone oDiagonal;
    oDiagonal.setNumElements(3);
    oDiagonal.setType(T3Board::eTYPE_MAIN_DIAGONAL);  
    oDiagonal.setID(lineID);
    oDiagonal.setOrdinal(0);
    this->addZone(oDiagonal);                

    // add the anti diagonal 
    lineID = "anti_diagonal";
    oDiagonal.setType(T3Board::eTYPE_ANTI_DIAGONAL);  
    oDiagonal.setID(lineID);
    oDiagonal.setOrdinal(0);    // unchanged
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