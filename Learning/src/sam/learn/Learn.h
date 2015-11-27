#ifndef __SAM_LEARN_LEARN_H
#define __SAM_LEARN_LEARN_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "sam/learn/Task.h"
#include "sam/learn/State.h"

namespace sam
{
namespace learn
{
class Learn
{
private:   
    float gamma;
    
public:
    Learn();
    
    float getGamma() {return gamma;};
    void setGamma(float value) {gamma = value;};

    // Compute the Q value from a state with one connection
    float computeQ(State& oToState);
    
    // returns the Qmatrix representation of a task's Q values
    static cv::Mat getTaskQMatrix(Task& oTask);
   
private:    
    // gets maximum Q value of all transitions from the given state
    float maxQFromState(State& oFromState);
    
    // fills a Qmatrix row using the transitions a the given state
    static void fillQMatrixRow(cv::Mat matRow, State& oState);
};

}
}

#endif
