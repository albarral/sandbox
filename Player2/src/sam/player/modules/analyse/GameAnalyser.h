#ifndef __SAM_PLAYER_GAMEANALYSER_H
#define __SAM_PLAYER_GAMEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>


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
// It triggers an analysis every time the board changes, but waits till changes are stable.
// Thus avoiding unnecessary analyses in transient situations. 
// The time used to consider board stability goes in minTimeStable parameter.
class GameAnalyser : public utils::Module, public BusUser
{
public:
    // states of GameAnalyser module
    enum eState
    {
        eSTATE_WAITING,              // the board has not changed since last analysis, wait for changes
        eSTATE_ANALYSING,          // the board has changed, analyse board to get best move
        eSTATE_DONE                   // the analysis is done, best move ready to be done
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool binhibited;                    // module inhibition through bus CO
    std::vector<BoardZone> lines2Check;    // list of changed lines that need to be checked
    int minTimeStable;                 // minimum time required to trust board stability
    GameBoard* pGameBoard;    // pointer to shared data object
    GameAction* pGameAction;      // pointer to shared data object
    int watcherState;                   // state of watcher module
    int stableTime;                      // accumulated time of watcher stability           
    //LineAnalyser oLineAnalyser;

public:
    GameAnalyser();
    
    // initializes the module 
    void init(GameBoard& oGameBoard, GameAction& oGameAction);
       
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    
    
    bool checkBoardStable();
    
    // processes the board changes in a line by line basis
    void processBoardChanges();

    // traces the changes in state
    void showStateChange();     
};

}
}
#endif
