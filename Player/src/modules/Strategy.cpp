/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Strategy.h"

namespace sam
{    
log4cxx::LoggerPtr Strategy::logger(log4cxx::Logger::getLogger("sam.player"));

Strategy::Strategy() 
{
    bestChance = eCHANCES_ZERO;     
}

void Strategy::attackRandom(cv::Mat& matrix, int myMark)
{
    // Search for the empty cells and choose one of them randomly
    std::vector<std::pair<int, int>> listEmptyCells;
    int i, j, x, z;
    
    for (i = 0; i < matrix.rows; i++)
    {
        for (j = 0; j < matrix.cols; j++)
        {
            if (matrix.at<int>(i,j) == GameBoard::eCELL_EMPTY)
            {
                listEmptyCells.push_back(std::make_pair(i,j));
            }
        }
    }
    
    int size = listEmptyCells.size();
    int randNum = rand() % size;
    std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
    x = selectedCell.first;
    z = selectedCell.second;

    matrix.at<int>(x,z) = myMark;

}

void Strategy::attackRandom2(cv::Mat& matrix, int myMark)
{
    // Search for the empty cells and choose one of them randomly
    std::vector<std::pair<int, int>> listEmptyCells;
    cv::Mat matRow;
    
    // get list of empty cells 
    for (int i=0; i<matrix.rows; i++)
    {
        matRow = matrix.row(i);                
        for (int j=0; j<matRow.cols; j++)
        {
            if (matRow.at<int>(j) == GameBoard::eCELL_EMPTY)
                listEmptyCells.push_back(std::make_pair(i,j));
        }
    }

    // move to a randomly selected empty cell
    int randNum = rand() % listEmptyCells.size();
    std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
    matrix.at<int>(selectedCell.first, selectedCell.second) = myMark;
}


// Checks all lines in the board (rows, columns & diagonals) in search of the best next move, the one with highest chances to win 
bool Strategy::attack(cv::Mat& matrix, int myMark)
{    
    int winChance;
    Line oLine;
    oLine.setMatrix(matrix);

    // we start the check with zero chances
    bestChance = eCHANCES_ZERO;     

    // check rows
    for (int i=0; i<matrix.rows; i++)
    {
        // analyse row & check the chances to win if selecting one of its cells
        oLine.checkRow(i, myMark, GameBoard::eCELL_EMPTY);        
        winChance = analyseLine(oLine);
        
        // if best chance for now, select a cell as best next move
        if (winChance > bestChance)
        {
            bestChance = winChance;
            selectCell(oLine);
        }
    }    

    // check columns
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check the chances to win if selecting one of its cells
        oLine.checkColumn(j, myMark, GameBoard::eCELL_EMPTY);        
        winChance = analyseLine(oLine);
        
        // if best chance for now, select a cell as best next move
        if (winChance > bestChance)
        {
            bestChance = winChance;
            selectCell(oLine);
        }
    }    
    
    // check diagonals
    for (int k=1; k<=2; k++)
    {
        // analyse column & check the chances to win if selecting one of its cells
        oLine.checkDiagonal(k, myMark, GameBoard::eCELL_EMPTY);        
        winChance = analyseLine(oLine);
        
        // if best chance for now, select a cell as best next move
        if (winChance > bestChance)
        {
            bestChance = winChance;
            selectCell(oLine);
        }
    }    
    
    // if found a move with chances to win, do it
    if (bestChance > eCHANCES_ZERO)
    {
        matrix.at<int>(bestMove[0], bestMove[1]) = myMark;
        return true;
    }
    else
        return false;
    
}


// (This is the core of the strategy)
// Analyzes the cells in the given line & returns the chances to win if one them is selected
// eCHANCES_ZERO:       0 empty -> nothing to do 
// eCHANCES_LOW:         some empty + some other's -> low chances (not with this line, but may help to fill other lines) 
// eCHANCES_MEDIUM:    3 empty -> medium chances (promising as it's first move in a line)
// eCHANCES_HIGH:        2 empty + 1 mine -> good chances (may yield to a win move next turn)
// eCHANCES_WINNER:     1 empty + 2 mine -> winner move (with this move you win the game)
int Strategy::analyseLine(Line& oLine)
{
    // we start with 0 chances (as if line was full)
    int lineCheck = eCHANCES_ZERO;
    
    // some empty, let's see ...
    if (oLine.getNumEmpties() > 0)
    {
        // some other's -> low chances
        if (oLine.getNumOthers() > 0)            
            lineCheck = eCHANCES_LOW;
        // 0 other's, let's check mines ...
        else
        {            
            switch (oLine.getNumMines())
            {               
                // 0 mine (3 empty) -> medium chances (first move)
                case 0:
                    lineCheck = eCHANCES_MEDIUM;
                    break;
                // 1 mine -> good chances
                case 1:
                    lineCheck = eCHANCES_HIGH;
                    break;
                // 2 mine -> winner move
                case 2:
                    lineCheck = eCHANCES_WINNER;
                    break;                    
            }            
        }
    }
    
    return lineCheck;
}


// Selects one of the empty cells from the given line & stores it as best move
void Strategy::selectCell(Line& oLine)
{
    // simply take the first option (if any)
    if (oLine.getListEmptyCells().size() != 0)
    {
        cv::Point cell = oLine.getListEmptyCells().at(0);
        bestMove[0] = cell.x;   // x stores the row
        bestMove[1] = cell.y;   // y stores the column
    }    
}
}