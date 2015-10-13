#ifndef __SAM_REWARDCALCULATOR_H
#define __SAM_REWARDCALCULATOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

namespace sam
{
class RewardCalculator
{
private:   
    static log4cxx::LoggerPtr logger;
    float kAttack;
    float kDefend;
    int dMaxVictory;
    int dMaxDefeat;
    
public:
    RewardCalculator();

    float getKAttack() {return kAttack;};
    void setKAttack(float value) {kAttack = value;};
    
    float getKDefend() {return kDefend;};
    void setKDefend(float value) {kDefend = value;};
    
    int getDMaxVictory() {return dMaxVictory;};
    void setDMaxVictory(int value) {dMaxVictory = value;};
    
    int getDMaxDefeat() {return dMaxDefeat;};
    void setDMaxDefeat(int value) {dMaxDefeat = value;};

    //return the value of each reward
    float static computeAttackReward(int kAttack, int dVictory, int dMaxVictory);
    float static computeDefendReward(int kDefend, int dDefeat, int dMaxDefeat);
};

}

#endif
