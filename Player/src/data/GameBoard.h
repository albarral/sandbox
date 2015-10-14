#ifndef __SAM_PLAYER_GAMEBOARD_H
#define __SAM_PLAYER_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <mutex>
//#include <vector>

#include "opencv2/core/core.hpp" //for the matrix

namespace sam
{
// This class represents 3x3 the game board.
// All methods mutex protected for safe simoultaneous access by multiple agents.
class GameBoard
{
public:
    static const int LINE_SIZE = 3;     // 3 cells for each board's line, column or diagonal
    static const int EMPTY_MARK = 0;     // mark for empty cells
    
//    enum eStatus  // game state
//    {
//        eSTAT_READY,                       // game not started
//        eSTAT_TURN_SAM,                 // SAM's turn
//        eSTAT_TURN_TAM,                 // TAM's turn
//        eSTAT_FINISHED_DRAW,          // game over with no winner	
//        eSTAT_FINISHED_WINNER
//    };
//    
//    enum eCell  //cell state
//    {
//        eCELL_EMPTY,        // empty cell
//        eCELL_SAM,	// cell occupied by SAM
//        eCELL_TAM	// cell occupied by TAM
//    };
        
private:   
    std::mutex mutex;
    cv::Mat matrix;                              // matrix of board cells (each with one of eCell values)              
//    int status;                                     // board status (one of eStatus values)
//    int numPlayers;
//    std::string winner;
//    std::vector<int> listTurns;             // list of turns
//    std::vector<int>::iterator it_turn;    // present turn     
    
public:
    GameBoard();
    
    // reset game board by emptying cells
    void reset();

//    //(mutex protected)    
//    int getStatus();
//    //(mutex protected)    
//    void setStatus(int value);
    
    cv::Mat getMatrix() {return matrix;};
    //int getNumPlayers() {return numPlayers;}
        
//    void setWinner(std::string name) {winner = name;};
//    std::string getWinner() {return winner;}
//    
//    // return present turn (mutex protected)
//    int getPresentTurn(); 
//    // sets turn randomly (mutex protected)
//    void initTurn();
//    // changes turn to next player (mutex protected)
//    void changeTurn();
    
    // puts a player's mark in the specified cell (mutex protected)
    void markCell(int mark, int row, int col);
    
//    // checks if game is over (mutex protected)
//    bool isGameOver();
//        
//    // gets board's status name
//    std::string getStatusName();
};

}

#endif
