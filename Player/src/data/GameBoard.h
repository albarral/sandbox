#ifndef __SAM_GAMEBOARD_H
#define __SAM_GAMEBOARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp" //for the matrix
#include <log4cxx/logger.h>

namespace sam
{
class GameBoard
{
public:
    enum eStatus  // game state
    {
        eSTAT_READY,			// game not started
	eSTAT_TURN_SAM,                 // SAM's turn
	eSTAT_TURN_TAM,			// TAM's turn
	eSTAT_FINISHED_DRAW,		// game over with no winner	
	eSTAT_FINISHED_SAM_WINS,        // SAM won the game
	eSTAT_FINISHED_TAM_WINS         // TAM won the game
    };
    
    enum eCell  //cell state
    {
	eCELL_EMPTY,                    // empty cell
	eCELL_SAM,			// cell occupied by SAM
	eCELL_TAM			// cell occupied by TAM
    };
        
private:   
    static log4cxx::LoggerPtr logger;
    int status;
    cv::Mat matrix;
    
public:
    GameBoard();
    
    int getStatus() {return status;};
    void setStatus(int value) {status = value;};
    
    cv::Mat getMatrix() {return matrix;};
    void setMatrix(cv::Mat value) {matrix = value;};
    
    // show a matrix with the values of the cells
    void ShowMatrix();
    // show the states
    void showStates();
};

}

#endif
