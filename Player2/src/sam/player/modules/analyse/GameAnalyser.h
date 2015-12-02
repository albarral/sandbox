#ifndef __SAM_PLAYER_GAMEANALYSER_H
#define __SAM_PLAYER_GAMEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <deque>
#include <log4cxx/logger.h>

#include "opencv2/core/core.hpp" //for the matrix

#include "sam/utils/Module.h"
#include "sam/player/bus/BusUser.h"
#include "sam/player/data/GameBoard.h"
#include "sam/player/data/GameAction.h"
#include "sam/player/utils/BoardZone.h"

namespace sam 
{
namespace player
{    
// This module analyzes the board and deduces the best moves for attack and defense.
// Analyses the changed lines every time the board changes. 
// To avoid unnecessary work, waits for changes to be stable before the analysis is done.
// Stability measure is controlled by requiredStableTime parameter.        
// Brooks IN:
// CO_ANALYSER_INHIBIT
// CO_ANALYSE_FULL          - forces exhaustive analysis of game board (not only of changed lines)
// SO_WATCHER_STATE
// SO_STABLE_TIME           - accumulated time of board stability
// Brooks OUT:    
// CO_WATCHER_ACK          - acknowledge detected changes (done when analysis about to start)
// SO_ANALYSER_STATE    
    
class GameAnalyser : public utils::Module, public BusUser
{
public:
    // states of GameAnalyser module
    enum eState
    {
        eSTATE_WAIT,                    // the board has not changed since last analysis, wait for changes
        eSTATE_ANALYSE,          // the board has changed, analyse board to get best move
        eSTATE_DONE                   // the analysis is done, best move ready to be done
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    cv::Mat matBoard;              // matrix representing the present board cells 
    std::deque<BoardZone> lines2Check;    // list of changed lines that need to be checked
    int requiredStableTime;          // minimum required time to trust board stability
    GameBoard* pGameBoard;    // pointer to shared data object
    GameAction* pGameAction;      // pointer to shared data object
    //LineAnalyser oLineAnalyser;
    // controls & sensors
    bool binhibited;                    // module inhibition
    bool bFullAnalysis;                 // requested analysis of the full board
    int watcherState;                   // state of watcher module
    int stableTime;                      // accumulated time of watcher stability           

public:
    GameAnalyser();
    
    // initializes the module 
    void init(GameBoard& oGameBoard, GameAction& oGameAction);
       
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    
    // checks if board is stable (watcher stable for enough time)
    bool checkBoardStable();
    // fetch board data (get the matrix and update the list of lines to be analysed)
    void fetchBoardData();
    // processes the board changes in a line by line basis
    void doAnalysis();

    // traces the changes in state
    void showStateName();     
};

}
}
#endif
