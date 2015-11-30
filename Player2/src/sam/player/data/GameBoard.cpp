/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/GameBoard.h"

namespace sam
{   
namespace player
{
GameBoard::GameBoard(int size)
{
    // 3x3 board
    matrix = cv::Mat_<uchar>(size,size);   
}

void GameBoard::updateInfo(cv::Mat& mat, std::vector<BoardZone> listChangedLines)
{
    std::lock_guard<std::mutex> locker(mutex);
    // updates matrix data
    mat.copyTo(matrix);
    // appends new changed lines to the present list
    linesChanged.insert(linesChanged.end(), listChangedLines.begin(), listChangedLines.end());
}

void GameBoard::getMatrixCopy(cv::Mat& matCopy)
{
    std::lock_guard<std::mutex> locker(mutex);
    // copies matrix data into matCopy
    matrix.copyTo(matCopy);    
}

void GameBoard::getChangedLinesCopy(std::vector<BoardZone>& listCopy)
{
    std::lock_guard<std::mutex> locker(mutex);
    listCopy = linesChanged;    
}

int GameBoard::getNumChangedLines()
{
    std::lock_guard<std::mutex> locker(mutex);
    return linesChanged.size();
}

void GameBoard::resetChangedLines()
{
    std::lock_guard<std::mutex> locker(mutex);
    linesChanged.clear();    
}
  
}
}