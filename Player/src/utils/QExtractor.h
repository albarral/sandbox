#ifndef __SAM_LEARN_QEXTRACTOR_H
#define __SAM_LEARN_QEXTRACTOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "learn/GameTask.h"
#include "learn/GameState.h"

namespace sam 
{
class QExtractor
{
private:
    cv::Mat matQ;
    
public:
    //QExtractor();
            
    cv::Mat getQMatrix() {return matQ;};
    
    // builds the Qmatrix representation of the given task
    void exploreTask(GameTask& oGameTask);

private:   
    // builds a Qmatrix row for the given state
    void exploreState(cv::Mat& matRow, GameState& oGameState);

};
}

#endif
