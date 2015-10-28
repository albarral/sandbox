#ifndef __SAM_PLAYER_H
#define __SAM_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "utils/module2.h"
#include "data/GameBoard.h"
#include "data/GameFlow.h"
#include "data/PlayerIdentity.h"
#include "modules/BoardSensor.h"
#include "modules/BoardActuator.h"
#include "modules/play/Line.h"

namespace sam 
{
// Agent (with own thread) that plays the tic-tac-toe game
// It derives from base class Module2
class Player : public Module2
{
public:
    // states of Player module
    enum eState
    {
        ePLAYER_OFF,			// initial state before game starts
        ePLAYER_WAIT,		// waiting for my turn
        ePLAYER_PLAY,		// it's my turn, do my move
        ePLAYER_FINISHED		// game is finished
    };

protected:
    static log4cxx::LoggerPtr logger;
    PlayerIdentity oPlayerIdentity;    // player's identity
    GameBoard oGameBoard;      // game's board
    GameFlow oGameFlow;          // game's flow
    bool bemptyCells;
    BoardSensor oBoardSensor;
    BoardActuator oBoardActuator;
    bool bFirstTurn;                        // indicates we had the first turn

public:
    Player();
    
    // initializes the module 
    virtual void init (std::string firstPlayerID);
    
    PlayerIdentity& getPlayerIdentity() {return oPlayerIdentity;};     
    
    // asks the player if game is finished for him
    bool isPlayerFinished();
    
protected:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    
    // select a proper cell in the game board (using any strategy) and mark it
    virtual void chooseCell() = 0;
    //check if there is a winner or the game is finished
    bool checkBoardOpen();
    // checks the observed line to see if there's a winner
    void analyseLine (Line& oLine);    
    // finish the game in a proper manner
    virtual void finishGame() = 0;
    
    // shows the next state name
    void showStateChange();    
    
};
}
#endif
