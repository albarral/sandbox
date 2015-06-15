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
    gamma = 0;   
}

// Q(state, action) = Reward(state, action) + gamma * max [Q(next state, all actions)]
float Learn::computeQ(Connection* pConnection, Place& oPlace)
{
    float reward, QNextState, Q;
     
    reward = oPlace.getReward();    
    QNextState = maxQvalue(oPlace);
    
    Q = reward + gamma * QNextState;
    pConnection->setQ(Q);
    
    return Q;
}

float Learn::maxQvalue(Place& oPlace)
{
    float maxQ = 0.0;
    float Q;
    std::vector<sam::Connection>& listConnection = oPlace.getListConnections();
    
    std::vector<sam::Connection>::iterator it_connection = listConnection.begin();
    std::vector<sam::Connection>::iterator it_end = listConnection.end();
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