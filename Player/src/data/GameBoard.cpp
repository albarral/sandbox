/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for the random values
#include <iterator>     // std::advance

#include "log4cxx/ndc.h"

#include "GameBoard.h"

namespace sam
{   
log4cxx::LoggerPtr GameBoard::logger(log4cxx::Logger::getLogger("sam.player"));

GameBoard::GameBoard()
{
    // 3x3 board
    matrix = cv::Mat_<int>(3,3);   
    numPlayers = 2;
    listTurns.push_back(eSTAT_TURN_SAM);
    listTurns.push_back(eSTAT_TURN_TAM);
    // set first turn by default
    it_turn = listTurns.begin();
    reset();
}

// reset gameboard
void GameBoard::reset()
{
    // empty all cells & set status to ready
    matrix = cv::Scalar(eCELL_EMPTY);
    status = eSTAT_READY;    
}

// set turn randomly
void GameBoard::initTurn()
{
    // select random player and assign turn to him
    int randomPlayer = rand() % numPlayers;         
    it_turn = listTurns.begin();
    std::advance(it_turn, randomPlayer);

    // set board status to present turn
    status = *it_turn;
}

void GameBoard::changeTurn()
{
    it_turn++;
    
    if (it_turn == listTurns.end())        
        it_turn = listTurns.begin();
    
    // set board status to present turn
    status = *it_turn;
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
