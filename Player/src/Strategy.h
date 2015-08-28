#ifndef STRATEGY_H
#define	STRATEGY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp" //for the matrix

#include "data/GameBoard.h"

namespace sam
{  
class Strategy 
{   
public:
    Strategy();
    
    static bool attack1(cv::Mat& matrix, int myMark);
    static bool attack2(cv::Mat& matrix, int myMark);
    static void attackRandom(cv::Mat& matrix, int myMark);

};
}

#endif

