#ifndef __SAM_PLAYER_GAMEBOARD_H
#define __SAM_PLAYER_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

#include "opencv2/core/core.hpp" //for the matrix

#include "sam/player/utils/BoardZone.h"

namespace sam
{
namespace player
{    
// (shared data) This class represents 3x3 the game board.
// It also stores the changed lines in the board.    
// mutex protected
class GameBoard
{
private:   
    std::mutex mutex;
    cv::Mat matrix;                             // matrix representing the present board cells 
    std::vector<BoardZone> linesChanged;      // list of changed lines in board (eLine values)
    
public:
    GameBoard(int size);
          
    // updates the matrix and the list of changed lines (updated together to grant coherence)
    void updateInfo(cv::Mat& mat, std::vector<BoardZone>& listChangedLines);    
    // gets a copy of the changed lines list
    void getChangedLinesCopy(std::vector<BoardZone>& listCopy);    
    // gets a copy of the matrix
    cv::Mat getMatrixCopy();    
    // get a copy of the specified board line
    cv::Mat getLineCopy(BoardZone& oZone);
    
    int getNumChangedLines();  
    // clears the changed lines list
    void resetChangedLines();
};

}
}
#endif
