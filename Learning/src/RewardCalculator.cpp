/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "RewardCalculator.h"

namespace sam
{   
log4cxx::LoggerPtr RewardCalculator::logger(log4cxx::Logger::getLogger("sam.player"));
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
    return (kDefend * (1 - (float(dDefeat)/float(dMaxDefeat))));
}

}