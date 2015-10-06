#ifndef __SAM_REWARDCALCULATOR_H
#define __SAM_REWARDCALCULATOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
class RewardCalculator
{
private:   
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

    //return the value of each reward with value between 0 and 1
    float static computeAttackReward(int kAttack, int dVictory, int dMaxVictory);
    float static computeDefendReward(int kDefend, int dDefeat, int dMaxDefeat);
};

}

#endif
