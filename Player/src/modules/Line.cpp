/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Line.h"

namespace sam
{    
Line::Line() 
{
    numMines = numOthers = numEmpties = 0;
}

void Line::reset()
{
    numMines = numOthers = numEmpties = 0;
    listEmptyCells.clear();    
}

// checks the cells in the specified matrix row
void Line::checkRow(int row, int myMark, int emptyMark)
{    
    this->myMark = myMark;
    this->emptyMark = emptyMark;

    reset();
    for (int j=0; j<mat.cols; j++)
    {
        checkCell(row, j, j);
    }
}

// checks the cells in the specified matrix column 
void Line::checkColumn(int col, int myMark, int emptyMark)
{    
    this->myMark = myMark;
    this->emptyMark = emptyMark;

    reset();
    for (int i=0; i<mat.rows; i++)
    {
        checkCell(i, col, i);
    }
}

// checks the cells in the specified matrix diagonal (1 for first diagonal, 2 for second one) 
void Line::checkDiagonal(int num, int myMark, int emptyMark)
{
    this->myMark = myMark;
    this->emptyMark = emptyMark;

    // assure it's a square matrix (otherwise it has no diagonals)
    if (mat.rows != mat.cols)
        return;
        
    reset();
    if (num == 1)
    {
        // walk first diagonal (from NW to SE)
        for (int k=0; k<mat.rows; k++)
        {
            checkCell(k, k, k);  
        }
    }
    else if (num == 2)
    {
        // walk second diagonal (from NE to SW)
        int topColumn = mat.cols - 1;
        for (int k=0; k<mat.rows; k++)
        {
            checkCell(k, topColumn - k, k);  
        }
    }
}

// Checks if the given cell is mine, others or empty. 
// It updates counters & the list of empty cells if it's the case
void Line::checkCell(int row, int col, int posLine)
{    
    int cellValue = mat.at<int>(row, col);

    // empty cells
    if (cellValue == emptyMark)            
    {
        numEmpties++;
        listEmptyCells.push_back(cv::Point(row, col));
        cells[posLine] = eCELL_EMPTY;
    }
    // my cells
    else if (cellValue == myMark)
    {
        numMines++;
        cells[posLine] = eCELL_MINE;
    }
    // others' cells
    else
    {
        numOthers++;   
        cells[posLine] = eCELL_OTHER;
    }
}
}