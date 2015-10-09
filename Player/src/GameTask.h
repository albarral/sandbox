#ifndef __SAM_GAMETASK_H
#define __SAM_GAMETASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "Task.h"
#include "learn/GameState.h"
#include "sam/utils/Database.h"

namespace sam 
{
class GameTask : public Task
{
public:
    // Tasks
    enum eType
    {
        eTASK_TICTACTOE
    };    
private:
    static log4cxx::LoggerPtr logger;
    Database oDatabase;
    std::vector<GameState> listGameStates;
    
public:
    GameTask();
    
    void init(int ID);
    
    std::vector<GameState>& getListGameStates() {return listGameStates;}; 
    void addGameState(GameState& oGameState);
    
private:
    void create();
    
    // shows brief description of given task
    void describeTask();
    // shows brief description of given state
    void describeState(GameState* pGameState);
      
    void buildTicTacToe();
};
}

#endif
