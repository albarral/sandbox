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
    matrix = cv::Mat::zeros(size, size, CV_8UC1);   
}

void GameBoard::updateInfo(cv::Mat& mat, std::vector<BoardZone>& listChangedLines)
{
    std::lock_guard<std::mutex> locker(mutex);
    // updates matrix data
    mat.copyTo(matrix);
    // appends new changed lines to the present list
    linesChanged.insert(linesChanged.end(), listChangedLines.begin(), listChangedLines.end());
}

void GameBoard::fetchInfo(cv::Mat& matCopy, std::vector<BoardZone>& listCopy)
{
    std::lock_guard<std::mutex> locker(mutex);
    // copies matrix data
    matrix.copyTo(matCopy);    
    // copies linesChanged list
    listCopy = linesChanged;        
}

cv::Mat GameBoard::getMatrixClone()
{
    std::lock_guard<std::mutex> locker(mutex);
    // clones matrix, generating a new Mat instance
    return matrix.clone();    
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