#ifndef __SAM_PLAYER_GAMEFLOW_H
#define __SAM_PLAYER_GAMEFLOW_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

#include "data/PlayerIdentity.h"

namespace sam
{
// This class represents the game flow.
// It holds the list of players & manages the game's turn.
// All methods mutex protected for safe simoultaneous access by multiple agents.
class GameFlow
{
public:
    enum eStatus  // game state
    {
        eGAME_READY,                       // game not started
        eGAME_PLAYING,               // game being played
        eGAME_OVER_DRAW,          // game over with no winner	
        eGAME_OVER_WINNER        // game over with a winner
    };

private:   
    std::mutex mutex;
    int status;                                     // game status (one of eStatus values)
    int numMoves;                               // moves done in a game
    std::vector<PlayerIdentity> listPlayers;             // list of players
    int turn;                                           // present turn (an index for listPlayers)    
    PlayerIdentity* winner;                     // game winner
    
public:
    GameFlow();
    
    // reset game flow (clears winner & sets status to ready)
    void resetGame();
    // reset list of players
    void resetPlayers();
    
    int getStatus();
    void setStatus(int value);
    // checks if game is over 
    bool isGameOver();
    
    int getNumMoves();
    
    // adds a new player to the game
    void addPlayer(PlayerIdentity& oPlayerIdentity);
   
    // sets turn randomly 
    void initTurn();
    //get the turn of the moment
    int getTurn() {return turn;};
    // changes turn to next player (mutex protected)
    void changeTurn();
    // gets the player that has the turn
    PlayerIdentity* getPlayerWithTurn();     
    // checks if it's a given player's turn
    
    // sets the game winner
    void setWinner(PlayerIdentity& oPlayerIdentity);
    // gets the identity of the game winner
    PlayerIdentity* getWinner();
        
    // gets name of flow status
    std::string getStatusName();
};

}

#endif
