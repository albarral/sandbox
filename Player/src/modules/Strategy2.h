#ifndef __SAM_PLAYER_STRATEGY2_H
#define __SAM_PLAYER_STRATEGY2_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "Learn.h"
#include "modules/Line.h"

namespace sam
{      
// Class used to follow SMART strategy (with learning capability) for playing the tic-tac-toe game.    
class Strategy2 
{
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;                     // true when functionality is initialized
    float bestReward;        // best reward of all possible attack movements (in present game state)
    int bestMove[2];          // the cell selection (row, col) that gives the maximum attack reward
    GameTask* pGameTask;    //  pointer to the game task
    Learn oLearn;                    // the learning capability
    
public:
    Strategy2();

    // enable Strategy2 functionality
    void init (GameTask& oGameTask);
    bool isEnabled() {return benabled;};
    
    // Checks the board and randomly select one of its empty cells. Storing it as best move.
    bool playRandom(cv::Mat& matrix, int myMark);
    
    // Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
    void playSmart(cv::Mat& matrix, int myMark);
    
    float getBestReward() {return bestReward;}
    int* getBestMove() {return bestMove;}

private:
    // checks if the given line holds the best move in the board 
    void checkBestMoveInLine(int lineType, int linePosition, Line& oLine);
        
    // analyzes the observed line to obtain the best rewarded movement
    Transition* analyseLine (Line& oLine);    

    Transition* findBestTransition(std::vector<sam::Transition>& listTransitions);

    std::string toStringBestMove();
};
}

#endif

