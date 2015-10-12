/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Learn.h"
#include "Transition.h"

namespace sam
{  
log4cxx::LoggerPtr Learn::logger(log4cxx::Logger::getLogger("sam.player"));
Learn::Learn()
{
    gamma = 0.8;   
}

// QAttack(state, action) = RewardAttack(state, action) + gamma * max [QAttack(next state, all actions)]
float Learn::computeQAttack(State& oState)
{
    float rewardA, QNextState, QAttack;
     
    rewardA = oState.getReward();    
    QNextState = maxQAttackValue(oState);
    
    QAttack = rewardA + gamma * QNextState;
       
    return QAttack;
}

// QDefend(state, action) = RewardDefend(state, action) + gamma * max [QDefend(next state, all actions)]
float Learn::computeQDefend(State& oState)
{
    float rewardD, QNextState, QDefend;
     
    rewardD = oState.getRewardDefense();    
    QNextState = maxQDefendValue(oState);
    
    QDefend = rewardD + gamma * QNextState;
       
    return QDefend;
}

float Learn::maxQAttackValue(State& oState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oState.getListTransitions();
    
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
    LOG4CXX_INFO(logger,"NextQmaxAttack: " << maxQ);
    return maxQ;
}

float Learn::maxQDefendValue(State& oState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oState.getListTransitions();
    
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
    LOG4CXX_INFO(logger,"NextQmaxDefense: " << maxQ);
    return maxQ;
}

}