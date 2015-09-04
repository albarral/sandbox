#ifndef __SAM_GAMEBOARD_H
#define __SAM_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

namespace sam
{
class GameBoard
{
public:
    enum eStatus  // game state
    {
        eSTAT_READY,                       // game not started
        eSTAT_TURN_SAM,                 // SAM's turn
        eSTAT_TURN_TAM,                 // TAM's turn
        eSTAT_FINISHED_DRAW,          // game over with no winner	
        eSTAT_FINISHED_SAM_WINS,   // SAM won the game
        eSTAT_FINISHED_TAM_WINS    // TAM won the game
    };
    
    enum eCell  //cell state
    {
        eCELL_EMPTY,        // empty cell
        eCELL_SAM,	// cell occupied by SAM
        eCELL_TAM	// cell occupied by TAM
    };
        
private:   
    static log4cxx::LoggerPtr logger;
    int status;                                     // board status (one of eStatus values)
    cv::Mat matrix;                              // matrix of board cells (each with one of eCell values)              
    int numPlayers;
    std::vector<int> listTurns;             // list of turns
    std::vector<int>::iterator it_turn;    // present turn     
    
public:
    GameBoard();
    
    // reset gameboard by emptying cells & setting status to ready
    void reset();
    
    int getStatus() {return status;};
    void setStatus(int value) {status = value;};
    
    cv::Mat getMatrix() {return matrix;};
    int getNumPlayers() {return numPlayers;}
        
    int getPresentTurn() {return *it_turn;};
    // set turn randomly
    void initTurn();
    // change turn to next player
    void changeTurn();
    
    // show a matrix with the values of the cells
    void ShowMatrix();
    // show the states
    void showStates();
};

}

#endif
