/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/


#include "sam/player/utils/QExtractor.h"
#include "sam/learn/Transition.h"

namespace sam 
{
namespace player
{ 
void QExtractor::exploreTask(GameTask& oGameTask)
{    
    int numStates = oGameTask.getListGameStates().size();
    // create new matrix if dimensions changed (ie. first time call)
    if (matQ.rows != numStates || matQ.cols != numStates)
    {
        matQ = cv::Mat(numStates, numStates, CV_32SC1);          // CV_8UC1   
        matQprev = matQ.clone();
    }
    matQ.copyTo(matQprev);
    matQ = cv::Scalar(0);
           
    // for each state, fill the corresponding Q matrix row
    for (auto& oGameState : oGameTask.getListGameStates()) 
    {
        cv::Mat matRow = matQ.row(oGameState.getID());
        exploreState(matRow, oGameState);        
    } 
    
    matDiff = matQ - matQprev;
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
}