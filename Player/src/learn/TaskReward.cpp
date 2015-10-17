/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "TaskReward.h"

namespace sam
{   
TaskReward::TaskReward()
{
    // UNUSED FOR NOW ...
    kAttack = 0;
    kDefend = 0;
    dMaxVictory = 0;
    dMaxDefeat = 0;
}

// Sets the rewards of the given task depending on its type (T3 attack, T3 defense ...)
void TaskReward::setTaskRewards(GameTask& oGameTask, int taskType)
{
    // walk list of states and set reward depending on task type
    std::vector<GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<GameState>::iterator it_end = oGameTask.getListGameStates().end();
    
    while (it_gameState != it_end)
    { 
        GameState& oGameState = *it_gameState;
        switch (taskType)
        {
            case eTASK_T3_ATTACK:
                setRewardT3Attack(oGameState);    
                break;

            case eTASK_T3_DEFENSE:
                setRewardT3Defense(oGameState);    
                break;
        }
        it_gameState++;
    }
}

// sets the reward for a state of the T3 attacking task
void TaskReward::setRewardT3Attack(GameState& oGameState)
{
    float reward;
    
    if (oGameState.getNumOthers() == 0)
    {
        reward = REWARD_SCALE*(float)(oGameState.getNumMines())/3.0;
    }  
    else
    {
        reward = 0;
    }
    
    oGameState.setReward(reward);    
}

// sets the reward for a state of the T3 defensive task
void TaskReward::setRewardT3Defense(GameState& oGameState)
{
    float reward;
    
    if (oGameState.getNumOthers() == 0 || oGameState.getNumMines() == 0 || oGameState.getNumOthers() < oGameState.getNumMines())
    {
        reward = 0;
    }  
    else if(oGameState.getNumOthers() > oGameState.getNumMines())
    {
        reward = REWARD_SCALE * (oGameState.getNumOthers() - oGameState.getNumMines());
    }
    
    oGameState.setReward(reward);        
}

//
//float TaskReward::computeAttackReward(int kAttack, int dVictory, int dMaxVictory)
//{  
//    return (kAttack * (1 - (float(dVictory)/float(dMaxVictory))));
//}
//
//float TaskReward::computeDefendReward(int kDefend, int dDefeat, int dMaxDefeat)
//{
//    int Rdefend;
//    if(dDefeat > 1)
//        Rdefend = kDefend * 0.5 * (float(dDefeat)/(float(dDefeat)-1));
//    else 
//        Rdefend = kDefend;
//                
//    return Rdefend;
//}

////calculate the distances and store them
//void Strategy2::computeStateDistances(GameState& oGameState)
//{    
//    int mines = oGameState.getNumMines();
//    int others = oGameState.getNumOthers();
//    
//    int distanceVictory = GameDistance::computeDistance2Victory(mines, others);
//    oGameState.setDVictory(distanceVictory);
//    
//    int distanceDefeat = GameDistance::computeDistance2Defeat(mines, others);
//    oGameState.setDDefeat(distanceDefeat);
//}
//
////calculate the rewards and store them
//void Strategy2::updateStateRewards(GameState& oGameState, RewardCalculator& oRewardCalculator)
//{
//    float rewardAttack = oRewardCalculator.computeAttackReward(oRewardCalculator.getKAttack(), oGameState.getDVictory(), oRewardCalculator.getDMaxVictory());
//    oGameState.setReward(rewardAttack);
//    
//    float rewardDefend = oRewardCalculator.computeDefendReward(oRewardCalculator.getKDefend(), oGameState.getDDefeat(), oRewardCalculator.getDMaxDefeat());
//    oGameState.setRewardDefense(rewardDefend);
//}

}