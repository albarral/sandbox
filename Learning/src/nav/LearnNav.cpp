/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "LearnNav.h"

namespace sam
{   
LearnNav::LearnNav()
{
    gamma = 0;   
}

// Q(state, action) = Reward(state, action) + gamma * max [Q(next state, all actions)]
float LearnNav::computeQ(Place& oPlace)
{
    float reward, QNextState, Q;
     
    reward = oPlace.getReward();    
    QNextState = maxQvalue(oPlace);
    
    Q = reward + gamma * QNextState;
       
    return Q;
}

float LearnNav::maxQvalue(Place& oPlace)
{
    float maxQ = 0.0;
    float Q;
    std::vector<Connection>& listConnection = oPlace.getListConnections();
    
    std::vector<Connection>::iterator it_connection = listConnection.begin();
    std::vector<Connection>::iterator it_end = listConnection.end();
    while (it_connection != it_end)
    {
        Q = it_connection->getQ();
        
        if (Q > maxQ)
        {
            maxQ = Q;            
        }
        it_connection ++;
    }
    return maxQ;
}

}