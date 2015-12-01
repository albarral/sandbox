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
          
    // both elements are updated together to grant coherence
    void updateInfo(cv::Mat& mat, std::vector<BoardZone>& listChangedLines);    
    // both elements are fetched together to grant coherence (returned values are copies, not permanent accesses to data)
    void fetchInfo(cv::Mat& matCopy, std::vector<BoardZone>& listCopy);    
    // returns matrix clone
    cv::Mat getMatrixClone();
    
    int getNumChangedLines();  
    void resetChangedLines();
};

}
}
#endif
