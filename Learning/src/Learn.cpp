/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Learn.h"
#include "Transition.h"

namespace sam
{  
Learn::Learn()
{
    gamma = 0;   
}

// Q(toState) = reward(toState) + gamma * max [Q(transitions from toState)]
float Learn::computeQ(State& oToState)
{
    float Q = oToState.getReward() + gamma * maxQFromState(oToState);
       
    return Q;
}

    
// gets max Q value of all transitions from the given state
float Learn::maxQFromState(State& oFromState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oFromState.getListTransitions();
    
    std::vector<sam::Transition>::iterator it_transition = listTransition.begin();
    std::vector<sam::Transition>::iterator it_end = listTransition.end();
    while (it_transition != it_end)
    {
        Q = it_transition->getQ();
        
        if (Q > maxQ)
        {
            maxQ = Q;            
        }
        it_transition ++;
    }
    return maxQ;
}

cv::Mat Learn::getTaskQMatrix(Task& oTask)
{
    int numStates = oTask.getListStates().size();
    cv::Mat matQ = cv::Mat(numStates, numStates, CV_8UC1);     
    matQ = cv::Scalar(0);
           
    // for each state, fill the corresponding Q matrix row
    for (auto& oState : oTask.getListStates()) 
    {
        cv::Mat matRow = matQ.row(oState.getID());
        fillQMatrixRow(matRow, oState);        
    }        

    return matQ;
}

void Learn::fillQMatrixRow(cv::Mat matRow, State& oState)
{
    // fill the Q row cells that correspond to a state transition
    for (auto& oTransition : oState.getListTransitions()) 
    {
        int j = oTransition.getNextState();
        matRow.at<int>(j) = (int)oTransition.getQ();        
    }                
}

}