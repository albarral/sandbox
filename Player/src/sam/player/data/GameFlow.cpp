/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for the random values

#include "sam/player/data/GameFlow.h"

namespace sam
{   
namespace player
{    
GameFlow::GameFlow()
{
    resetGame();
    resetPlayers();
}

// reset game flow (clears winner & sets status to ready)
void GameFlow::resetGame()
{
    std::lock_guard<std::mutex> locker(mutex);
    status = eGAME_READY;
    numMoves = 0;
    winner = 0;
}

void GameFlow::resetPlayers()
{
    std::lock_guard<std::mutex> locker(mutex);
    listPlayers.clear();
    turn = 0;
}

int GameFlow::getStatus() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return status;
}

void GameFlow::setStatus(int value) 
{
    std::lock_guard<std::mutex> locker(mutex);
    status = value;
}

// checks if game is over
bool GameFlow::isGameOver()
{
    std::lock_guard<std::mutex> locker(mutex);    
    return (status == GameFlow::eGAME_OVER_WINNER || status == GameFlow::eGAME_OVER_DRAW);
}

int GameFlow::getNumMoves()
{
    std::lock_guard<std::mutex> locker(mutex);    
    return numMoves;    
}

void GameFlow::addPlayer(PlayerIdentity& oPlayerIdentity)
{    
    std::lock_guard<std::mutex> locker(mutex);    
    listPlayers.push_back(oPlayerIdentity);        
}

// set turn randomly
void GameFlow::initTurn()
{
    std::lock_guard<std::mutex> locker(mutex);
    // select random player
    turn = rand() % listPlayers.size();
}

void GameFlow::changeTurn()
{
    std::lock_guard<std::mutex> locker(mutex);
    // advance turn, rolling back to 0 if list end reached
    turn++;    
    numMoves++;
    if (turn == listPlayers.size())        
        turn = 0;
}
  
PlayerIdentity* GameFlow::getPlayerWithTurn()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (listPlayers.size() > 0)
        return &(listPlayers.at(turn));
    // if no players defined zero is returned
    else 
        return 0;
}

void GameFlow::setWinner(PlayerIdentity& oPlayerIdentity)
{
    std::lock_guard<std::mutex> locker(mutex);
    winner = &oPlayerIdentity;    
}

PlayerIdentity* GameFlow::getWinner()
{
    std::lock_guard<std::mutex> locker(mutex);
    return winner;
}


std::string GameFlow::getStatusName()
{
    std::string name;
    switch (getStatus())
    {
        case eGAME_READY:
            name = "Ready to start";
            break;
            
        case eGAME_PLAYING:
            name = "Playing";
            break;
                        
        case eGAME_OVER_DRAW:
            name = "Finished draw";
            break;
            
        case eGAME_OVER_WINNER:
            name = "Finished winner";
            break;
    }   // end switch    

    return name;
}

}
}