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
    
    bool attack1(cv::Mat& matrix, GameBoard* pBoard);
    bool attack2(cv::Mat& matrix, GameBoard* pBoard);
    void attackRandom(cv::Mat& matrix, GameBoard* pBoard);

};
}

#endif

