#ifndef __SAM_LINE_H
#define __SAM_LINE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp" // for the cv matrix

namespace sam
{  
namespace player
{     
// Class used to check lines in a matrix, one at a time, being rows, columns or diagonals. 
// It obtains the number of cells in the checked line that are owned by each player. And also the list of empty positions in the line.     
class Line 
{  
public:
    // line types
    enum eType
    {
        eTYPE_ROW,        // line is a row
        eTYPE_COL,        // line is a column
        eTYPE_DIAG1,     // line is the ascending diagonal
        eTYPE_DIAG2      // line is the descending diagonal
    };
    // line identifiers
    enum eLine 
    {
        eLINE_ROW1,
        eLINE_ROW2,
        eLINE_ROW3,
        eLINE_COL1,  
        eLINE_COL2,
        eLINE_COL3,
        eLINE_DIAG1,
        eLINE_DIAG2,
        eLINE_DIM   // dimension of eLine enum
    };
    // cell states
    enum eCell  
    {
        eCELL_EMPTY,        // empty cell
        eCELL_MINE,	// cell occupied by me
        eCELL_OTHER	// cell occupied by the other player
    };
    
private:
    cv::Mat mat;        // matrix to be checked
    int myMark;         // value hold by my cells
    int cells[3];    
    int emptyMark;    // value hold by empty cells  
    int numMines;       // number of cells marked as mine
    int numOthers;      // number of cells marked as others'
    int numEmpties;     // number of empty cells
    std::vector<cv::Point> listEmptyCells;    // positions of empty cells (if any) in the line
    
public:
    Line();
    
    void setMatrix(cv::Mat& matrix) {mat = matrix;}
    
    // checks the given line (row, column or diagonal) computing which cells are mine, others or empty
    void checkRow (int row, int myMark, int emptyMark);
    void checkColumn (int col, int myMark, int emptyMark);
    void checkDiagonal (int lineType, int myMark, int emptyMark);

    int* getCells() {return cells;}
    int getNumMines() {return numMines;};
    int getNumOthers() {return numOthers;};
    int getNumEmpties() {return numEmpties;};
    std::vector<cv::Point>& getListEmptyCells() {return listEmptyCells;}
    
    // translates a given line type & position to a specific line identifier
    static int getLineIdentifier(int lineType, int linePos);
    
private:
    // reset line counters
    void reset();
    // check the cell at the given position
    void checkCell (int row, int col, int posLine);
};
}
}

#endif

