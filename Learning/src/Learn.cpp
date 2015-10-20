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
    gamma = 0;   
}

// Q(toState) = reward(toState) + gamma * max [Q(transitions from toState)]
float Learn::computeQ(State& oToState)
{
    float Q = oToState.getReward() + gamma * maxQFromState(oToState);
       
    return Q;
}

    
// gets max Q value of all transitions from the given state
float Learn::maxQFromState(State& oFromState)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Transition>& listTransition = oFromState.getListTransitions();
    
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