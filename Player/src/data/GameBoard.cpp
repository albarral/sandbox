/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"
#include "GameBoard.h"

using namespace log4cxx;

namespace sam
{   
LoggerPtr GameBoard::logger(Logger::getLogger("sam.gameBoard"));

GameBoard::GameBoard()
{
    matrix = cv::Mat_<int>(cv::Mat::zeros(3,3, CV_8U));   
    status = eSTAT_READY;
    showStates();
}

void GameBoard::ShowMatrix()
{
    LOG4CXX_INFO(logger, "\n " << matrix);
}

void GameBoard::showStates()
{
    std::string state;
    switch (getStatus())
    {
        case eSTAT_READY:
            state = "Ready to start";
            break;
            
        case eSTAT_TURN_SAM:
            state = "Sam's turn";
            break;
            
        case eSTAT_TURN_TAM:
            state = "Tam's turn";
            break;
        case eSTAT_FINISHED_DRAW:
            state = "The game ended in a draw";
            break;
            
        case eSTAT_FINISHED_SAM_WINS:
            state = "Sam wins";
            break;
            
        case eSTAT_FINISHED_TAM_WINS:
            state = "Tam wins";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << state);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(state);   
}

}
