/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for the random values
#include <iterator>     // std::advance

#include "GameBoard.h"

namespace sam
{   
GameBoard::GameBoard()
{
    // 3x3 board
    matrix = cv::Mat_<int>(3,3);   
    numPlayers = 2;
    winner = "";
    listTurns.push_back(eSTAT_TURN_SAM);
    listTurns.push_back(eSTAT_TURN_TAM);
    // set first turn by default
    it_turn = listTurns.begin();
    reset();
}

// reset gameboard
void GameBoard::reset()
{
    std::lock_guard<std::mutex> locker(mutex);
    // empty all cells & set status to ready
    matrix = cv::Scalar(eCELL_EMPTY);
    status = eSTAT_READY;    
}

int GameBoard::getStatus() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return status;
};

void GameBoard::setStatus(int value) 
{
    std::lock_guard<std::mutex> locker(mutex);
    status = value;
};

int GameBoard::getPresentTurn() 
{
    std::lock_guard<std::mutex> locker(mutex);    
    return *it_turn;
};

// set turn randomly
void GameBoard::initTurn()
{
    std::lock_guard<std::mutex> locker(mutex);

    // select random player and assign turn to him
    int randomPlayer = rand() % numPlayers;         
    it_turn = listTurns.begin();
    std::advance(it_turn, randomPlayer);

    // set board status to present turn
    status = *it_turn;
}

void GameBoard::changeTurn()
{
    std::lock_guard<std::mutex> locker(mutex);

    it_turn++;    
    if (it_turn == listTurns.end())        
        it_turn = listTurns.begin();
    
    // set board status to present turn
    status = *it_turn;
}

// puts a player's mark in the specified cell
void GameBoard::markCell(int mark, int row, int col)
{
    std::lock_guard<std::mutex> locker(mutex);    
    matrix.at<int>(row, col) = mark;
}
  
// checks if game is over (mutex protected)
bool GameBoard::isGameOver()
{
    std::lock_guard<std::mutex> locker(mutex);    
    return (status == GameBoard::eSTAT_FINISHED_DRAW || status == GameBoard::eSTAT_FINISHED_WINNER);
}

std::string GameBoard::getStatusName()
{
    std::string name;
    switch (getStatus())
    {
        case eSTAT_READY:
            name = "Ready to start";
            break;
            
        case eSTAT_TURN_SAM:
            name = "Sam's turn";
            break;
            
        case eSTAT_TURN_TAM:
            name = "Tam's turn";
            break;
            
        case eSTAT_FINISHED_DRAW:
            name = "finished draw";
            break;
            
        case eSTAT_FINISHED_WINNER:
            name = "finished winner";
            break;
    }   // end switch    

    return name;
}

}
