/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "RewardCalculator.h"

namespace sam
{   
RewardCalculator::RewardCalculator()
{
    kAttack = 0;
    kDefend = 0;
    dMaxVictory = 0;
    dMaxDefeat = 0;
}

float RewardCalculator::computeAttackReward(int kAttack, int dVictory, int dMaxVictory)
{  
    return (kAttack * (1 - (float(dVictory)/float(dMaxVictory))));
}

float RewardCalculator::computeDefendReward(int kDefend, int dDefeat, int dMaxDefeat)
{
    int Rdefend;
    if(dDefeat > 1)
        Rdefend = kDefend * 0.5 * (float(dDefeat)/(float(dDefeat)-1));
    else 
        Rdefend = kDefend;
                
    return Rdefend;
}

}