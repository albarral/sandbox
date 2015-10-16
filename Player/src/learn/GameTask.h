#ifndef __SAM_PLAYER_GAMETASK_H
#define __SAM_PLAYER_GAMETASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Task.h"
#include "learn/GameState.h"
#include "sam/utils/Database.h"

namespace sam 
{
class GameTask : public Task
{
private:
    Database oDatabase;
    std::vector<GameState> listGameStates;
    
public:
    GameTask();
    
    void init(int ID);
    
    std::vector<GameState>& getListGameStates() {return listGameStates;}; 
    void addGameState(GameState& oGameState);
    
    void storeInMemo2();
    void loadFromMemo2();
    
private:    
    void gameStatesFromMemo(sql::Connection* con);
};
}

#endif
