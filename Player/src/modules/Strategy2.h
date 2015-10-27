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
public:
    enum eLine 
    {
        eLINE_ROW1,
        eLINE_ROW2,
        eLINE_ROW3,
        eLINE_COL1,  
        eLINE_COL2,
        eLINE_COL3,
        eLINE_DIAG1,
        eLINE_DIAG2
    };
private:
    static log4cxx::LoggerPtr logger;
    bool benabled;                     // true when functionality is initialized
    float bestReward;        // best reward of all possible attack movements (in present game state)
    int bestMove[2];          // the cell selection (row, col) that gives the maximum attack reward
    GameTask* pGameTask;    //  pointer to the game task
    Learn oLearn;                    // the learning capability
    bool bexplorative;
    int selectedLine;
    std::vector<Transition> listExploredTransitions;
    
public:
    Strategy2();

    // enable Strategy2 functionality
    void init (GameTask& oGameTask);
    bool isEnabled() {return benabled;};
    
    void setExplorativeMode(bool bvalue) {bexplorative = bvalue;};
    bool isExplorativeMode() {return bexplorative;};
    
    // Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
    void playSmart(cv::Mat& matrix, int myMark);
    
    float getBestReward() {return bestReward;};
    int* getBestMove() {return bestMove;};
    
    int getSelectedLine() {return selectedLine;};
    void setSelectedLine(int value) {selectedLine = value;};

private:
    // checks if the given line holds the best move in the board 
    void checkBestMoveInLine(int lineType, int linePosition, Line& oLine);
        
    // analyzes the observed line to obtain the best rewarded movement
    Transition* analyseLine (Line& oLine);    

    // gets the state that represents the given line configuration 
    GameState* deduceState4Line(Line& oLine);
    
    Transition* findBestTransition(GameState& oFromState);
    
    void findBestMove(Transition& oBestTransition, int lineType, int linePosition, Line& oLine);

    std::string toStringBestMove();
};
}

#endif

