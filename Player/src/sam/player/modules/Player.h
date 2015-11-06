#ifndef __SAM_PLAYER_H
#define __SAM_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/utils/module2.h"
#include "sam/player/data/GameBoard.h"
#include "sam/player/data/GameFlow.h"
#include "sam/player/data/PlayerIdentity.h"
#include "sam/player/modules/BoardSensor.h"
#include "sam/player/modules/BoardActuator.h"
#include "sam/player/modules/PlayerPurpose.h"
#include "sam/player/modules/play/Line.h"

namespace sam 
{
namespace player
{    
// Base class for player agents
// This class launches the thread where the agent lives.
// It also controls the agent's states flow to allow it playing the tic-tac-toe game.
// It senses & acts on the game board through the BoardSensor & BoardActuator objects.
// It has its own identity & purpose thanks to the PlayerIdentity & PlayerPurpose objects.    
// The player's purpose must be instantiated in Player derived classes.
// It derives from base class Module2
class Player : public Module2
{
public:
    // states of Player module
    enum eState
    {
        ePLAYER_READY,		// initial state before game starts
        ePLAYER_START,		// first state when game starts
        ePLAYER_WAIT,		// waiting for my turn
        ePLAYER_PLAY,		// it's my turn, do my move
        ePLAYER_FINISHED		// game is finished
    };

protected:
    static log4cxx::LoggerPtr logger;
    PlayerIdentity oPlayerIdentity;         // player's identity
    PlayerPurpose* pPlayerPurpose;     // player's purpose (determines the will to play & the playing mode) 
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
    PlayerPurpose& getPlayerPurpose() {return *pPlayerPurpose;}
    
    // asks the player if game is finished for him
    bool isPlayerFinished();
    
protected:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             

    // checks if board is empty
    bool checkBoardEmpty();
    // clear the board
    void doClearBoard();
    
    // select a proper cell in the game board (using any strategy) and mark it
    virtual void chooseCell() = 0;
    //check if there is a winner or the game is finished
    bool checkBoardOpen();
    // checks the observed line to see if there's a winner
    void analyseLine (Line& oLine);    
    // finish the game in a proper manner
    virtual void endOfGame() = 0;
    
    
private:    
    // shows the next state name
    void showStateChange();        
    
};
}
}
#endif
