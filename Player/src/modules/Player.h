#ifndef __SAM_PLAYER_H
#define __SAM_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "utils/module2.h"
#include "data/GameBoard.h"
#include "data/GameFlow.h"
#include "data/PlayerIdentity.h"
#include "learn/GameTask.h"
#include "modules/Line.h"
#include "modules/Strategy2.h"
#include "modules/BoardSensor.h"
#include "modules/BoardActuator.h"

namespace sam 
{
// Module that performs an agent that plays the tic-tac-toe game
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

private:
    static log4cxx::LoggerPtr logger;
    PlayerIdentity oPlayerIdentity;    // player's identity
    GameBoard oGameBoard;      // game's board
    GameFlow oGameFlow;          // game's flow
    bool bemptyCells;
    GameTask oAttackTask;            // ofensive task
    GameTask oDefenseTask;        // defensive task  
    Strategy2 oAttackStrategy;            // ofensive strategy
    Strategy2 oDefenseStrategy;         // defensive strategy 
    BoardSensor oBoardSensor;
    BoardActuator oBoardActuator;
    bool bFirstTurn;                        // indicates we had the first turn
    bool stored;

public:
    Player();
    
    // initializes the module 
    void init (std::string firstPlayerID);
    
    PlayerIdentity& getPlayerIdentity() {return oPlayerIdentity;};     
//    std::string getID() {return ID;};
//    void setID(std::string value) {ID = value;};
    
    // asks the player if game is finished for him
    bool isPlayerFinished();
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    
    void bestMovement(cv::Mat& matrix);
    //Put in the matrix the cell selected by the player
    void chooseCell();
    //check if there is a winner or the game is finished
    bool checkBoardOpen();
    // checks the observed line to see if there's a winner
    void analyseLine (Line& oLine);    
 
    // shows the next state name
    void showStateChange();    
    
};
}
#endif
