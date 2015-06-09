/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Learn.h"
#include "Transition.h"
#include "Environment.h"

namespace sam
{
Learn::Learn()
{
    gamma = 0;   
}

float Learn::maxQvalue(Place oPlace) //(place, listPlaces)
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
    }
    return maxQ;
}


float Learn::computeQ(Connection oConn)
{
    Environment oEnv;
    Place oPlace;
    gamma = 0.8;
    int nxtPlc;
    float rwrd, QNextState, Q;
     
    nxtPlc = oConn.getNextPlace();
    oPlace = oEnv.getListPlaces().at(nxtPlc);
    rwrd = oPlace.getReward();    
    QNextState = maxQvalue(oPlace);
    
    Q = rwrd + gamma * QNextState;
    oConn.setQ(Q);
    
    return Q;

}

}