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
#include "sam/player/data/GameAction.h"
#include "sam/player/data/GameBoard.h"
#include "sam/player/data/PlayerData.h"
#include "sam/player/modules/analyse/LineAnalyser2.h"
#include "sam/player/utils/BoardZone.h"
#include "sam/player/utils/GameMove.h"

namespace sam 
{
namespace player
{    
// This module analyzes the board and gets the best possible moves (for attack and defense).
// It triggers a new analysis after each board change (only checking changed lines).
// Exhaustive analysis of all lines can be forced through CO input.
// Board stability is required before each analysis to avoid glitching results (waiting time in param requiredStableTime).
// Brooks IN:
// CO_ANALYSER_INHIBIT
// CO_ANALYSE_FULL          - forces exhaustive board analysis (all lines)
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
        eSTATE_WAIT,                // board is changing, wait for change to finish
        eSTATE_ANALYSE,          // board change finished, analyse board 
        eSTATE_DONE               // analysis done, wait for next change
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    // params
    int requiredStableTime;          // minimum required time to trust board stability
    // shared data
    GameBoard* pGameBoard;      // sensed board 
    GameAction* pGameAction;      // next move  
    PlayerData* pPlayerData;         // marks and play mode
    // logic
    cv::Mat matBoard;              // matrix of present board
    std::deque<BoardZone> lines2Check;    // list of changed lines that need to be checked
    LineAnalyser oLineAnalyser;    // tool for line analysis
    GameMove oAttackMove;
    GameMove oDefenseMove;
    // controls & sensors
    bool binhibited;                    // module inhibition
    bool bFullAnalysis;                 // requested analysis of the full board
    int watcherState;                   // state of watcher module
    int stableTime;                      // accumulated time of watcher stability           

public:
    GameAnalyser();
    
    // initializes the module 
    void init(GameBoard& oGameBoard, GameAction& oGameAction, PlayerData& oPlayerData);
       
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
    // get the specified zone (line) from the board
    cv::Mat getLineFromBoard(BoardZone& oZone);

    // traces the changes in state
    void showStateName();     
};

}
}
#endif
