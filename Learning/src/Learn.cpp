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

float Learn::maxQvalue(Place oPlace)
{
    float maxQ = 0.0;
    float q;
    std::vector<sam::Connection> listConn = oPlace.getListConnections();
    
    std::vector<sam::Connection>::iterator it_connection = listConn.begin();
    std::vector<sam::Connection>::iterator it_end = listConn.end();
    while (it_connection != it_end)
    {
        q = it_connection -> getQ();
        
        if (q > maxQ)
        {
            maxQ = q;
            
        }
        it_connection ++;
    }
    return maxQ;
}


float Learn::computeQ(Connection oConn, Place oPlace)
{
    gamma = 0.8;
    float rwrd, QNextState, Q;
     
    rwrd = oPlace.getReward();    
    QNextState = maxQvalue(oPlace);
    
    Q = rwrd + gamma * QNextState;
    oConn.setQ(Q);
    
    return Q;
}

}