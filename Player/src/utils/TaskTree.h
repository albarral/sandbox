#ifndef __SAM_PLAYER_TASKTREE_H
#define __SAM_PLAYER_TASKTREE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "Transition.h"

namespace sam 
{
class TaskTree
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
    TaskTree();
        
    // shows full description of given task
    static void showTask(GameTask& oGameTask);    
    // shows full description of given state
    static void showState(GameState& oGameState);
    
    // shows brief description of given task
    static void showTask2(GameTask& oGameTask, bool bfilterOut = false);    
    // shows brief description of given state
    static void showState2(GameState& oGameState, GameTask& oGameTask, bool bfilterOut);
    // shows brief description of given transition
    static void showTransition2(Transition& oTransition, GameTask& oGameTask, bool bfilterOut);
    
    // returns the Qmatrix representation of a task's Q values
    static void getTaskQMatrix(cv::Mat& matQ, GameTask& oGameTask);

private:   
    // fills a Qmatrix row using the transitions a the given state
    static void fillQMatrixRow(cv::Mat& matRow, GameState& oGameState);

};
}

#endif
