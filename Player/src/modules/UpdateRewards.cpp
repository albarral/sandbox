/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "UpdateRewards.h"
#include "learn/GameDistance.h"
#include "RewardCalculator.h"

namespace sam
{    
UpdateRewards::UpdateRewards() {}

//calculate the distances and store them
void UpdateRewards::computeDistances(GameState& oGameState)
{
    GameDistance oGameDistance;
    int mines = oGameState.getNumMines();
    int others = oGameState.getNumOthers();
    
    int distanceVictory = oGameDistance.computeDistance2Victory(mines, others);
    oGameState.setDVictory(distanceVictory);
    
    int distanceDefeat = oGameDistance.computeDistance2Defeat(mines, others);
    oGameState.setDDefeat(distanceDefeat);
}

//calculate the rewards and store them
void UpdateRewards::computeRewards(GameState& oGameState)
{
    RewardCalculator oRewardCalculator;

    float rewardAttack = oRewardCalculator.computeAttackReward(oRewardCalculator.getKAttack(), 
            oGameState.getDVictory(), oRewardCalculator.getDMaxVictory());
    oGameState.setReward(rewardAttack);
    
    float rewardDefend = oRewardCalculator.computeDefendReward(oRewardCalculator.getKDefend(), 
            oGameState.getDDefeat(), oRewardCalculator.getDMaxDefeat());
    oGameState.setRewardDefense(rewardDefend);
}

}