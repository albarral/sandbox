#ifndef __SAM_PLAYER_GAMEBOARD_H
#define __SAM_PLAYER_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <mutex>
//#include <vector>

#include "opencv2/core/core.hpp" //for the matrix

namespace sam
{
// This class represents 3x3 the game board.
// All methods mutex protected for safe simoultaneous access by multiple agents.
class GameBoard
{
public:
    static const int LINE_SIZE = 3;     // 3 cells for each board's line, column or diagonal
    static const int EMPTY_MARK = 0;     // mark for empty cells 
        
private:   
    std::mutex mutex;
    cv::Mat matrix;                              // matrix of board cells (each with one of eCell values)              
    
public:
    GameBoard();
    
    // reset game board by emptying cells
    void reset();
  
    cv::Mat getMatrix() {return matrix;};
    
    // puts a player's mark in the specified cell (mutex protected)
    void markCell(int mark, int row, int col);    
};

}

#endif
