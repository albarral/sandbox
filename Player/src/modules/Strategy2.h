#ifndef __SAM_PLAYER_STRATEGY2_H
#define __SAM_PLAYER_STRATEGY2_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "learn/GameTask.h"
#include "Learn.h"
#include "Line.h"

namespace sam
{      
// Class used to follow SMART strategy (with learning capability) for playing the tic-tac-toe game.    
class Strategy2 
{
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;                     // true when functionality is initialized
    float bestAttackReward;        // best reward of all possible attack movements (in present game state)
    float bestDefenseReward;     // best reward of all possible defense movements (in present game state)
    int bestAttackMove[2];          // the cell selection (row, col) that gives the maximum attack reward
    int bestDefenseMove[2];      // the cell selection (row, col) that gives the maximum defense reward
    GameTask* pGameTask;    //  pointer to the game task
    Learn oLearn;                    // the learning capability
    
public:
    Strategy2();

    // enable Strategy2 functionality
    void init (GameTask& oGameTask);
    bool isEnabled() {return benabled;};
    
    // Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
    void playSmart(cv::Mat& matrix, int myMark);
    
    float getBestAttackReward() {return bestAttackReward;}
    float getBestDefenseReward() {return bestDefenseReward;}
    int* getBestAttackMove() {return bestAttackMove;}
    int* getBestDefenseMove() {return bestDefenseMove;}

private:
    // checks if this board's line holds the best attack or defense moves at present
    void checkBestMovesInLine(Line& oLine);
    
    Transition* getBestAttackTransition(std::vector<sam::Transition>& listTransitions);
    Transition* getBestDefenseTransition(std::vector<sam::Transition>& listTransitions);
    
    // analyzes the observed line to obtain the best rewards of attack & defense movements
    void analyseLine (Line& oLine, float& attackReward, float& defenseReward);    
    // stores one of the line's available moves as best attack move 
    void storeAttackMove (Line& oLine);
    // stores one of the line's available moves as best defense move
    void storeDefenseMove (Line& oLine);    
};
}

#endif

