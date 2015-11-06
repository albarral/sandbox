/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/GameBoard.h"

namespace sam
{   
namespace player
{
GameBoard::GameBoard()
{
    // 3x3 board
    matrix = cv::Mat_<int>(3,3);   
    reset();
}

// reset game board
void GameBoard::reset()
{
    std::lock_guard<std::mutex> locker(mutex);
    // empty all cells 
    matrix = cv::Scalar(EMPTY_MARK);
    //status = eSTAT_READY;    
}

// puts a player's mark in the specified cell
void GameBoard::markCell(int mark, int row, int col)
{
    std::lock_guard<std::mutex> locker(mutex);    
    matrix.at<int>(row, col) = mark;
}
  
}
}