#ifndef __SAM_GAMEBOARD_H
#define __SAM_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

#include "opencv2/core/core.hpp" //for the matrix

namespace sam
{
// This class represents 3x3 the game board.
// It may be accessed & modified by various agents simultaneously, so most of its methods are mutex protected.
class GameBoard
{
public:
    enum eStatus  // game state
    {
        eSTAT_READY,                       // game not started
        eSTAT_TURN_SAM,                 // SAM's turn
        eSTAT_TURN_TAM,                 // TAM's turn
        eSTAT_FINISHED_DRAW,          // game over with no winner	
        eSTAT_FINISHED_WINNER
    };
    
    enum eCell  //cell state
    {
        eCELL_EMPTY,        // empty cell
        eCELL_SAM,	// cell occupied by SAM
        eCELL_TAM	// cell occupied by TAM
    };
        
private:   
    std::mutex mutex;
    cv::Mat matrix;                              // matrix of board cells (each with one of eCell values)              
    int status;                                     // board status (one of eStatus values)
    int numPlayers;
    std::string winner;
    std::vector<int> listTurns;             // list of turns
    std::vector<int>::iterator it_turn;    // present turn     
    
public:
    GameBoard();
    
    // reset gameboard by emptying cells & setting status to ready (mutex protected)    
    void reset();

    //(mutex protected)    
    int getStatus();
    //(mutex protected)    
    void setStatus(int value);
    
    cv::Mat getMatrix() {return matrix;};
    int getNumPlayers() {return numPlayers;}
        
    void setWinner(std::string name) {winner = name;};
    std::string getWinner() {return winner;}
    
    // return present turn (mutex protected)
    int getPresentTurn(); 
    // sets turn randomly (mutex protected)
    void initTurn();
    // changes turn to next player (mutex protected)
    void changeTurn();
    
    // puts a player's mark in the specified cell (mutex protected)
    void markCell(int mark, int row, int col);
    
    // checks if game is over (mutex protected)
    bool isGameOver();
        
    // gets board's status name
    std::string getStatusName();
};

}

#endif
