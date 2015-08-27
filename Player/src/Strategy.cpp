/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Strategy.h"

namespace sam
{    
Strategy::Strategy() {}

bool Strategy::attack1(cv::Mat& matrix, int turn)
{
    // Search for a row, column or diagonal with one cell occupied and the others two empty and choose one of them
    int i, x, z;
    bool winner = false;
    std::vector<std::pair<int, int>> listEmptyCells;
    int emptyCell = sam::GameBoard::eCELL_EMPTY;
    
    if (!winner)
    {
        // Check possibilities to continue on rows
        for (i = 0; i < matrix.rows; i++)
        {
            if (matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == emptyCell && matrix.at<int>(i,2) == turn)
            {
                listEmptyCells.push_back(std::make_pair(i,0));
                listEmptyCells.push_back(std::make_pair(i,1));
                winner = true;
            }
            else if (matrix.at<int>(i,1) == matrix.at<int>(i,2) && matrix.at<int>(i,1) == emptyCell && matrix.at<int>(i,0) == turn)
            {
                listEmptyCells.push_back(std::make_pair(i,1));
                listEmptyCells.push_back(std::make_pair(i,2));
                winner = true;
            }
            else if (matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) == emptyCell && matrix.at<int>(i,1) == turn)
            {
                listEmptyCells.push_back(std::make_pair(i,0));
                listEmptyCells.push_back(std::make_pair(i,2));
                winner = true;
            }
        }
        
        // Check possibilities to continue on columns
        for (i = 0; i < matrix.cols; i++)
        {
            if (matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == emptyCell && matrix.at<int>(2, i) == turn)
            {
                listEmptyCells.push_back(std::make_pair(0, i));
                listEmptyCells.push_back(std::make_pair(1, i));
                winner = true;
            }
            else if (matrix.at<int>(1,i) == matrix.at<int>(2,i) && matrix.at<int>(1,i) == emptyCell && matrix.at<int>(0, i) == turn)
            {
                listEmptyCells.push_back(std::make_pair(1, i));
                listEmptyCells.push_back(std::make_pair(2, i));
                winner = true;
            }
            else if (matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) == emptyCell && matrix.at<int>(1, i) == turn)
            {
                listEmptyCells.push_back(std::make_pair(0, i));
                listEmptyCells.push_back(std::make_pair(2, i));
                winner = true;
            }
        }
        
        //Check possibilities to continue on diagonal top-left to bottom-right
        if (matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == emptyCell && matrix.at<int>(2, 2) == turn)
        {
            listEmptyCells.push_back(std::make_pair(0, 0));
            listEmptyCells.push_back(std::make_pair(1, 1));
            winner = true;
        }
        else if (matrix.at<int>(1,1) == matrix.at<int>(2,2) && matrix.at<int>(1,1) == emptyCell && matrix.at<int>(0,0) == turn)
        {
            listEmptyCells.push_back(std::make_pair(1, 1));
            listEmptyCells.push_back(std::make_pair(2, 2));
            winner = true;
        }
        else if (matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) == emptyCell && matrix.at<int>(1,1) == turn)
        {
            listEmptyCells.push_back(std::make_pair(0, 0));
            listEmptyCells.push_back(std::make_pair(2, 2));
            winner = true;
        }
        
        //Check possibilities to continue on diagonal top-right to bottom-left
        if (matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == emptyCell && matrix.at<int>(0,2) == turn)
        {
            listEmptyCells.push_back(std::make_pair(2, 0));
            listEmptyCells.push_back(std::make_pair(1, 1));
            winner = true;
        }
        else if (matrix.at<int>(1,1) == matrix.at<int>(0,2) && matrix.at<int>(1,1) == emptyCell && matrix.at<int>(2,0) == turn)
        {
            listEmptyCells.push_back(std::make_pair(1, 1));
            listEmptyCells.push_back(std::make_pair(0, 2));
            winner = true;
        }
        else if (matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) == emptyCell && matrix.at<int>(1,1) == turn)
        {
            listEmptyCells.push_back(std::make_pair(2, 0));
            listEmptyCells.push_back(std::make_pair(0, 2));
            winner = true;
        }
    }
    
    if (winner)
    {
        int size = listEmptyCells.size();
        int randNum = rand() % size;
        std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
        x = selectedCell.first;
        z = selectedCell.second;
        
        matrix.at<int>(x,z) = turn;

        return true;
    }
    else
        return false;
}

bool Strategy::attack2(cv::Mat& matrix, int turn)
{
    // Search for a row, column or diagonal with two cells occupied and the other empty and choose this
    int i, x, z;
    bool winner = false;
    int emptyCell = sam::GameBoard::eCELL_EMPTY;
    
    if (!winner)
    {
        // Check possibilities to win on rows
        for (i = 0; i < matrix.rows; i++)
        {
            if (matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == turn && matrix.at<int>(i,2) == emptyCell)
            {
                x = i;
                z = 2;
                winner = true;
                break;
            }
            else if (matrix.at<int>(i,1) == matrix.at<int>(i,2) && matrix.at<int>(i,1) == turn && matrix.at<int>(i,0) == emptyCell)
            {
                x = i;
                z = 0;
                winner = true;
                break;
            }
            else if (matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) == turn && matrix.at<int>(i,1) == emptyCell)
            {
                x = i;
                z = 1;
                winner = true;
                break;
            }
        }
        
        // Check possibilities to win on columns
        for (i = 0; i < matrix.cols; i++)
        {
            if (matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == turn && matrix.at<int>(2, i) == emptyCell)
            {
                x = 2;
                z = i;
                winner = true;
                break;
            }
            else if (matrix.at<int>(1,i) == matrix.at<int>(2,i) && matrix.at<int>(1,i) == turn && matrix.at<int>(0, i) == emptyCell)
            {
                x = 0;
                z = i;
                winner = true;
                break;
            }
            else if (matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) == turn && matrix.at<int>(1, i) == emptyCell)
            {
                x = 1;
                z = i;
                winner = true;
                break;
            }
        }
        
        //Check possibilities to win on diagonal top-left to bottom-right
        if (matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == turn && matrix.at<int>(2, 2) == emptyCell)
        {
            x = 2;
            z = 2;
            winner = true;
        }
        else if (matrix.at<int>(1,1) == matrix.at<int>(2,2) && matrix.at<int>(1,1) == turn && matrix.at<int>(0,0) == emptyCell)
        {
            x = 0;
            z = 0;
            winner = true;
        }
        else if (matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) == turn && matrix.at<int>(1,1) == emptyCell)
        {
            x = 1;
            z = 1;
            winner = true;
        }
        //Check possibilities to win on diagonal top-right to bottom-left
        if (matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == turn && matrix.at<int>(0,2) == emptyCell)
        {
            x = 0;
            z = 2;
            winner = true;
        }
        else if (matrix.at<int>(1,1) == matrix.at<int>(0,2) && matrix.at<int>(1,1) == turn && matrix.at<int>(2,0) == emptyCell)
        {
            x = 2;
            z = 0;
            winner = true;
        }
        else if (matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) == turn && matrix.at<int>(1,1) == emptyCell)
        {
            x = 1;
            z = 1;
            winner = true;
        }
    }
    
    if (winner)
    {
        matrix.at<int>(x,z) = turn;

        return true;
    }
    else
        return false;
}

void Strategy::attackRandom(cv::Mat& matrix, int turn)
{
    // Search for the empty cells and choose one of them randomly
    std::vector<std::pair<int, int>> listEmptyCells;
    int i, j, x, z;
    
    for (i = 0; i < matrix.rows; i++)
    {
        for (j = 0; j < matrix.cols; j++)
        {
            if (matrix.at<int>(i,j) == 0)
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

    matrix.at<int>(x,z) = turn;

}

}