/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

//#include <vector>

#include "QExtractor.h"
#include "Transition.h"

namespace sam 
{
void QExtractor::exploreTask(GameTask& oGameTask)
{
     int numStates = oGameTask.getListGameStates().size();
    if (matQ.rows != numStates || matQ.cols != numStates)
    {
        matQ = cv::Mat(numStates, numStates, CV_32SC1);          // CV_8UC1   
    }
    matQ = cv::Scalar(0);
           
    // for each state, fill the corresponding Q matrix row
    for (auto& oGameState : oGameTask.getListGameStates()) 
    {
        cv::Mat matRow = matQ.row(oGameState.getID());
        exploreState(matRow, oGameState);        
    }        
}

void QExtractor::exploreState(cv::Mat& matRow, GameState& oGameState)
{
    // fill the Q row cells that correspond to a state transition
    for (auto& oTransition : oGameState.getListTransitions()) 
    {
        int j = oTransition.getNextState();
        matRow.at<int>(j) = (int)oTransition.getQ();        
    }                
}

}