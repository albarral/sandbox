#ifndef  __SAM_STRATEGY_H
#define __SAM_STRATEGY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "data/GameBoard.h"
#include "Line.h"

namespace sam
{      
// Class to define winner strategies when playing the tic-tac-toe game.    
class Strategy 
{
public:        
    // Chances to win when selecting a cell from a given line (row, column or diagonal) 
    enum eChance
    {
        eCHANCES_ZERO,         // 3 cells filled -> can't move in this line
        eCHANCES_LOW,           // some cells empty & some from others -> few chances to win (not with this line)
        eCHANCES_MEDIUM,         // 3 cells empty -> first move in a line (low chances, but promising)
        eCHANCES_HIGH,        // 1 cell mine, 2 empty -> good move ahead
        eCHANCES_WINNER       // 2 cells mine, 1 empty -> winner move ahead
    };

private:
    static log4cxx::LoggerPtr logger;
    int bestChance;        // best chance to win at the present game board's configuration
    int bestMove[2];      // cell selection (row, col) that gives this best change to win     
    
public:
    Strategy();
    
    static bool attack1(cv::Mat& matrix, int myMark);
    static bool attack2(cv::Mat& matrix, int myMark);
    static void attackRandom(cv::Mat& matrix, int myMark);
        
    // Checks all lines in the board (rows, columns & diagonals) in search of the next best move
    // Returns true if a cell was selected, false otherwise
    bool attack(cv::Mat& matrix, int myMark);
    int getBestChance() {return bestChance;}
    int* getBestMove() {return bestMove;}

private:
    // analyzes the observed line & returns its best possible move
    int analyseLine (Line& oLine);    
    // selects one of the empty cells from the given line & stores it as best move
    void selectCell (Line& oLine);
    
};
}

#endif

