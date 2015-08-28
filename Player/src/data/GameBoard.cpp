/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"
#include "GameBoard.h"

namespace sam
{   
log4cxx::LoggerPtr GameBoard::logger(log4cxx::Logger::getLogger("sam.player"));

GameBoard::GameBoard()
{
    reset();
}

void GameBoard::reset()
{
    // reset gameboard by emptying cells & setting status to ready
    matrix = cv::Mat_<int>(3,3);   
    matrix = cv::Scalar(eCELL_EMPTY);
    status = eSTAT_READY;    
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
