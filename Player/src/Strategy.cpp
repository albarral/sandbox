/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Strategy.h"

namespace sam
{    
Strategy::Strategy() {}

bool Strategy::attack1(cv::Mat& matrix, GameBoard* pBoard)
{
    int i, x, z;
    bool winner = false;
    std::vector<std::pair<int, int>> listEmptyCells;
    int status = pBoard->getStatus();
    
    if(!winner)
    {
        // Check possibilities to continue on rows
        for(i = 0; i < matrix.rows; i++)
        {
            if(matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == 0 && matrix.at<int>(i,2) == status)
            {
                listEmptyCells.push_back(std::make_pair(i,0));
                listEmptyCells.push_back(std::make_pair(i,1));
                winner = true;
            }
            else if(matrix.at<int>(i,1) == matrix.at<int>(i,2) && matrix.at<int>(i,1) == 0 && matrix.at<int>(i,0) == status)
            {
                listEmptyCells.push_back(std::make_pair(i,1));
                listEmptyCells.push_back(std::make_pair(i,2));
                winner = true;
            }
            else if(matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) == 0 && matrix.at<int>(i,1) == status)
            {
                listEmptyCells.push_back(std::make_pair(i,0));
                listEmptyCells.push_back(std::make_pair(i,2));
                winner = true;
            }
        }
        // Check possibilities to continue on columns
        for(i = 0; i < matrix.cols; i++)
        {
            if(matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == 0 && matrix.at<int>(2, i) == status)
            {
                listEmptyCells.push_back(std::make_pair(0, i));
                listEmptyCells.push_back(std::make_pair(1, i));
                winner = true;
            }
            else if(matrix.at<int>(1,i) == matrix.at<int>(2,i) && matrix.at<int>(1,i) == 0 && matrix.at<int>(0, i) == status)
            {
                listEmptyCells.push_back(std::make_pair(1, i));
                listEmptyCells.push_back(std::make_pair(2, i));
                winner = true;
            }
            else if(matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) == 0 && matrix.at<int>(1, i) == status)
            {
                listEmptyCells.push_back(std::make_pair(0, i));
                listEmptyCells.push_back(std::make_pair(2, i));
                winner = true;
            }
        }
        //Check possibilities to continue on diagonal top-left to bottom-right
        if(matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == 0 && matrix.at<int>(2, 2) == status)
        {
            listEmptyCells.push_back(std::make_pair(0, 0));
            listEmptyCells.push_back(std::make_pair(1, 1));
            winner = true;
        }
        else if(matrix.at<int>(1,1) == matrix.at<int>(2,2) && matrix.at<int>(1,1) == 0 && matrix.at<int>(0,0) == status)
        {
            listEmptyCells.push_back(std::make_pair(1, 1));
            listEmptyCells.push_back(std::make_pair(2, 2));
            winner = true;
        }
        else if(matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) == 0 && matrix.at<int>(1,1) == status)
        {
            listEmptyCells.push_back(std::make_pair(0, 0));
            listEmptyCells.push_back(std::make_pair(2, 2));
            winner = true;
        }
        //Check possibilities to continue on diagonal top-right to bottom-left
        if(matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == 0 && matrix.at<int>(0,2) == status)
        {
            listEmptyCells.push_back(std::make_pair(2, 0));
            listEmptyCells.push_back(std::make_pair(1, 1));
            winner = true;
        }
        else if(matrix.at<int>(1,1) == matrix.at<int>(0,2) && matrix.at<int>(1,1) == 0 && matrix.at<int>(2,0) == status)
        {
            listEmptyCells.push_back(std::make_pair(1, 1));
            listEmptyCells.push_back(std::make_pair(0, 2));
            winner = true;
        }
        else if(matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) == 0 && matrix.at<int>(1,1) == status)
        {
            listEmptyCells.push_back(std::make_pair(2, 0));
            listEmptyCells.push_back(std::make_pair(0, 2));
            winner = true;
        }
    }
    if(winner)
    {
        int size = listEmptyCells.size();
        int randNum = rand() % size;
        std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
        x = selectedCell.first;
        z = selectedCell.second;
        
        if(status == sam::GameBoard::eSTAT_TURN_SAM)
        {
            matrix.at<int>(x,z) = sam::GameBoard::eCELL_SAM;
            pBoard->setMatrix(matrix);
        }
        else if(status == sam::GameBoard::eSTAT_TURN_TAM)
        {
            matrix.at<int>(x,z) = sam::GameBoard::eCELL_TAM;
            pBoard->setMatrix(matrix);
        }
        return true;
    }
    else
        return false;
}
bool Strategy::attack2(cv::Mat& matrix, GameBoard* pBoard)
{
    int i, x, z;
    bool winner = false;
    int status = pBoard->getStatus();
    
    if(!winner)
    {
        // Check possibilities to win on rows
        for(i = 0; i < matrix.rows; i++)
        {
            if(matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == status && matrix.at<int>(i,2) == 0)
            {
                x = i;
                z = 2;
                winner = true;
                break;
            }
            else if(matrix.at<int>(i,1) == matrix.at<int>(i,2) && matrix.at<int>(i,1) == status && matrix.at<int>(i,0) == 0)
            {
                x = i;
                z = 0;
                winner = true;
                break;
            }
            else if(matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) == status && matrix.at<int>(i,1) == 0)
            {
                x = i;
                z = 1;
                winner = true;
                break;
            }
        }
        // Check possibilities to win on columns
        for(i = 0; i < matrix.cols; i++)
        {
            if(matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == status && matrix.at<int>(2, i) == 0)
            {
                x = 2;
                z = i;
                winner = true;
                break;
            }
            else if(matrix.at<int>(1,i) == matrix.at<int>(2,i) && matrix.at<int>(1,i) == status && matrix.at<int>(0, i) == 0)
            {
                x = 0;
                z = i;
                winner = true;
                break;
            }
            else if(matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) == status && matrix.at<int>(1, i) == 0)
            {
                x = 1;
                z = i;
                winner = true;
                break;
            }
        }
        //Check possibilities to win on diagonal top-left to bottom-right
        if(matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == status && matrix.at<int>(2, 2) == 0)
        {
            x = 2;
            z = 2;
            winner = true;
        }
        else if(matrix.at<int>(1,1) == matrix.at<int>(2,2) && matrix.at<int>(1,1) == status && matrix.at<int>(0,0) == 0)
        {
            x = 0;
            z = 0;
            winner = true;
        }
        else if(matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) == status && matrix.at<int>(1,1) == 0)
        {
            x = 1;
            z = 1;
            winner = true;
        }
        //Check possibilities to win on diagonal top-right to bottom-left
        if(matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == status && matrix.at<int>(0,2) == 0)
        {
            x = 0;
            z = 2;
            winner = true;
        }
        else if(matrix.at<int>(1,1) == matrix.at<int>(0,2) && matrix.at<int>(1,1) == status && matrix.at<int>(2,0) == 0)
        {
            x = 2;
            z = 0;
            winner = true;
        }
        else if(matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) == status && matrix.at<int>(1,1) == 0)
        {
            x = 1;
            z = 1;
            winner = true;
        }
    }
    if(winner)
    {
        if(status == sam::GameBoard::eSTAT_TURN_SAM)
        {
            matrix.at<int>(x,z) = sam::GameBoard::eCELL_SAM;
            pBoard->setMatrix(matrix);
        }
        else if(status == sam::GameBoard::eSTAT_TURN_TAM)
        {
            matrix.at<int>(x,z) = sam::GameBoard::eCELL_TAM;
            pBoard->setMatrix(matrix);
        }
        return true;
    }
    else
        return false;
}

void Strategy::attackRandom(cv::Mat& matrix, GameBoard* pBoard)
{
    std::vector<std::pair<int, int>> listEmptyCells;
    int i, j, x, z;
    
    for(i = 0; i < matrix.rows; i++)
    {
        for(j = 0; j < matrix.cols; j++)
        {
            if(matrix.at<int>(i,j) == 0)
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
    
    if(pBoard->getStatus() == sam::GameBoard::eSTAT_TURN_SAM)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_SAM;
        pBoard->setMatrix(matrix);
    }
    else if(pBoard->getStatus() == sam::GameBoard::eSTAT_TURN_TAM)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_TAM;
        pBoard->setMatrix(matrix);
    }
}

}