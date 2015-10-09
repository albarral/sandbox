#ifndef __SAM_LEARNSTRATEGY_H
#define __SAM_LEARNSTRATEGY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "learn/GameState.h"

namespace sam
{        
class LearnStrategy 
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
    LearnStrategy();
    
    //search the best movement to do on the Qlearn mode
    void bestMovement(cv::Mat matrix);
    
private:
    //Serch for each GameState, if it match with a line of the board
    //If match, save the GameState in a new vector
    std::vector<GameState>& getBoardGameStates(cv::Mat matrix, std::vector<sam::GameState>& listGameStates);
    
};
}

#endif

