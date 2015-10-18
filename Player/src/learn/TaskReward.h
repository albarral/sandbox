#ifndef __SAM_PLAYER_TASKREWARD_H
#define __SAM_PLAYER_TASKREWARD_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "learn/GameTask.h"
#include "learn/GameState.h"

namespace sam
{
class TaskReward
{
public:
    static const int REWARD_SCALE = 100; 
    enum eTaskType
    {
        eTASK_T3_ATTACK,        // TicTacToe attacking task
        eTASK_T3_DEFENSE       // TicTacToe defensive task
    };
    
private:   
    float kAttack;
    float kDefend;
    
public:
    TaskReward();

    float getKAttack() {return kAttack;};
    void setKAttack(float value) {kAttack = value;};
    
    float getKDefend() {return kDefend;};
    void setKDefend(float value) {kDefend = value;};
        
    // sets the rewards of the given task depending on its type (T3 attack, T3 defense ...)
    static void setTaskRewards(GameTask& oGameTask, int taskType);

private:        
    // sets the reward for a state of the T3 attacking task
    static void setRewardT3Attack(GameState& oGameState);
    // sets the reward for a state of the T3 defensive task
    static void setRewardT3Defense(GameState& oGameState);
};

}

#endif
