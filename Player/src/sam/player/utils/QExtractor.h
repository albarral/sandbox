#ifndef __SAM_LEARN_QEXTRACTOR_H
#define __SAM_LEARN_QEXTRACTOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "sam/player/learn/GameTask.h"
#include "sam/player/learn/GameState.h"

namespace sam 
{
namespace player
{ 
class QExtractor
{
private:
    cv::Mat matQ;           // Q matrix obtained from task
    cv::Mat matQprev;    // Q matrix obtained in previous call
    cv::Mat matDiff;        // Q matrix changes = matQ - matQprev
    
public:
    //QExtractor();
            
    cv::Mat getQMatrix() {return matQ;};
    cv::Mat getDiffMatrix() {return matDiff;};
    
    // builds the Qmatrix representation of the given task
    void exploreTask(GameTask& oGameTask);
    
private:   
    // builds a Qmatrix row for the given state
    void exploreState(cv::Mat& matRow, GameState& oGameState);

};
}
}

#endif
