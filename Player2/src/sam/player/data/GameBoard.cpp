/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/GameBoard.h"
#include "sam/player/data/T3Board.h"

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

void GameBoard::getChangedLinesCopy(std::vector<BoardZone>& listCopy)
{
    std::lock_guard<std::mutex> locker(mutex);
    // copies linesChanged list
    listCopy = linesChanged;        
}

cv::Mat GameBoard::getMatrixCopy()
{
    std::lock_guard<std::mutex> locker(mutex);
    // clones matrix, generating a new Mat instance
    return matrix.clone();    
}

// Get a copy of the specified board line
cv::Mat GameBoard::getLineCopy(BoardZone& oZone)
{
    std::lock_guard<std::mutex> locker(mutex);
    
    cv::Mat matLine;
    switch (oZone.getType())
    {
        case T3Board::eZONE_ROW:
            matLine = matrix.row(oZone.getOrdinal());
            break;

        case T3Board::eZONE_COL:
            matLine = matrix.col(oZone.getOrdinal());
            break;

        case T3Board::eZONE_MAIN_DIAGONAL:
            matLine = matrix.diag(0);
            break;

        case T3Board::eZONE_ANTI_DIAGONAL:
        {
            // a matrix antidiagonal is the main diagonal of the matrix's vertical flip
            cv::Mat matFlip = matrix.clone();
            // fast vertical flip
            matrix.row(0).copyTo(matFlip.row(2));
            matrix.row(2).copyTo(matFlip.row(0));
            matLine = matFlip.diag(0);
            break;               
        }
        
        default:
            matLine = matrix;
    }

    return matLine.clone();    
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