/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Learn.h"
#include "Transition.h"

namespace sam
{   
Learn::Learn()
{
    gamma = 0.8;   
}

// QAttack(state, action) = RewardAttack(state, action) + gamma * max [QAttack(next state, all actions)]
float Learn::computeQAttack(GameState& oGameState)
{
    float rewardA, QNextState, QAttack;
     
    rewardA = oGameState.getReward();    
    QNextState = maxQAttackValue(oGameState);
    
    QAttack = rewardA + gamma * QNextState;
       
    return QAttack;
}

// QDefend(state, action) = RewardDefend(state, action) + gamma * max [QDefend(next state, all actions)]
float Learn::computeQDefend(GameState& oGameState)
{
    float rewardD, QNextState, QDefend;
     
    rewardD = oGameState.getRewardDefense();    
    QNextState = maxQDefendValue(oGameState);
    
    QDefend = rewardD + gamma * QNextState;
       
    return QDefend;
}

float Learn::maxQAttackValue(GameState& oGameState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oGameState.getListTransitions();
    
    std::vector<sam::Transition>::iterator it_transition = listTransition.begin();
    std::vector<sam::Transition>::iterator it_end = listTransition.end();
    while (it_transition != it_end)
    {
        Q = it_transition->getQ();
        
        if (Q > maxQ)
        {
            maxQ = Q;            
        }
        it_transition ++;
    }
    return maxQ;
}

float Learn::maxQDefendValue(GameState& oGameState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oGameState.getListTransitions();
    
    std::vector<sam::Transition>::iterator it_transition = listTransition.begin();
    std::vector<sam::Transition>::iterator it_end = listTransition.end();
    while (it_transition != it_end)
    {
        Q = it_transition->getQDefend();
        
        if (Q > maxQ)
        {
            maxQ = Q;            
        }
        it_transition ++;
    }
    return maxQ;
}

}