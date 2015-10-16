/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Learn.h"
#include "Transition.h"

namespace sam
{  
log4cxx::LoggerPtr Learn::logger(log4cxx::Logger::getLogger("sam.learn"));
Learn::Learn()
{
    gamma = 0.8;   
}

// Q(state, action) = Reward(state, action) + gamma * max [Q(next state, all actions)]
float Learn::computeQ(State& oState)
{
    float reward, QNextState, Q;
     
    reward = oState.getReward();    
    QNextState = maxQValue(oState);
    
    Q = reward + gamma * QNextState;
       
    return Q;
}


float Learn::maxQValue(State& oState)
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
    return maxQ;
}

}