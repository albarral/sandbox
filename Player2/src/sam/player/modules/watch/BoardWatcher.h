#ifndef __SAM_PLAYER_BOARDWATCHER_H
#define __SAM_PLAYER_BOARDWATCHER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "opencv2/core/core.hpp" //for the matrix

#include "sam/utils/Module.h"
#include "sam/player/bus/BusUser.h"
#include "sam/player/data/GameBoard.h"
#include "sam/player/data/T3Board.h"
#include "sam/player/utils/BoardZone.h"

namespace sam 
{
namespace player
{    
// This module monitors the board and extracts the board matrix.
// It also checks which lines have changed.
// It stores this info in the shared GameBoard object.    
class BoardWatcher : public utils::Module, public BusUser
{
public:
    // states of BoardWatcher module
    enum eState
    {
        eSTATE_STABLE,              // the board is stable, board configuration equal to last check
        eSTATE_CHANGING,          // the board is changing, board configuration changed since last check
        eSTATE_LOST                   // the board is lost, can't detect the board or sense its configuration  
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool binhibited;                    // module inhibition through bus CO
    T3Board oT3Board;
    cv::Mat matrixNow;                // matrix representing the present board cells 
    cv::Mat matrixPrev;                // matrix representing the previous board cells 
    std::vector<BoardZone> linesChanged;    // list of changed lines in the last check
    int timeStable;                      // accumulated time in STABLE state (from last change)
    GameBoard* pGameBoard;    // pointer to shared data object

public:
    BoardWatcher();
    
    // initializes the module 
    void init(GameBoard& oGameBoard);
       
protected:    
    // Search the board. Returns true if found, false otherwise.
    virtual bool searchBoard() = 0;
    // Senses the game board and informs a representing matrix (matrixNow). Returns true if sensed, false otherwise.
    virtual bool senseBoard() = 0;

private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    
    // checks board changes and informs the shared GameBoard object
    void processBoard();
    // increases timeStable with last elapsed time
    void updateStableTime();
    // resets timeStable to 0
    void resetStableTime();

    // detect changes in rows
    void checkChangedRows(cv::Mat& matDif);
    // detect changes in columns
    void checkChangedColumns(cv::Mat& matDif);
    // detect changes in both diagonals
    void checkChangedDiagonals(cv::Mat& matDif);
    
    // traces the changes in state
    void showStateChange();     
};

}
}
#endif
