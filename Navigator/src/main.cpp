/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 
#include <iostream> // for cout
#include <vector>

// Learning classes
#include "Connection.h"
#include "VirtualEnvironment.h"

using namespace std;

void testEnvironment(sam::VirtualEnvironment& oVirtualEnvironment);
int selectConnection(std::vector<sam::Connection>& listConnections);

// main program
int main(int argc, char** argv) 
{
    sam::VirtualEnvironment oVirtualEnvironment;
  
    // note: this must be done only the first time!
    //createEnvironment(oVirtualEnvironment);
    // note: this must be done next times!
    //loadEnvironment(oVirtualEnvironment);   
    
    oVirtualEnvironment.init(1);
       
    cout << endl << "test testEnvironment ..." << endl;
    testEnvironment(oVirtualEnvironment);
    
    oVirtualEnvironment.init(2);
    
    cout << endl << "test testEnvironment ..." << endl;
    testEnvironment(oVirtualEnvironment);
      
    sleep(1);   // not needed
    
    return 0;
}


void testEnvironment(sam::VirtualEnvironment& oVirtualEnvironment)
{
    int nextConnectionID;
        
    oVirtualEnvironment.setPlaceNow(5);
    cout << "Initial place: " << oVirtualEnvironment.getPlaceNow() <<endl;
    
    for (int i=0; i<3; i++)
    {
        std::vector<sam::Connection>& listConnections = oVirtualEnvironment.getPresentConnections();
        nextConnectionID = selectConnection(listConnections);
        oVirtualEnvironment.crossConnection(nextConnectionID);    
        cout << "new place: " << oVirtualEnvironment.getPlaceNow() <<endl;
    }
    
    return;
}

// selects the connection with the lowest cost to traverse
int selectConnection(std::vector<sam::Connection>& listConnections)
{        
    vector<sam::Connection>::iterator it_connection = listConnections.begin();
    vector<sam::Connection>::iterator it_end = listConnections.end();
    float cost, minCost = 1000;
    sam::Connection* winner = 0;
    // walk the list of connections and tracks the one with lowest cost
    while (it_connection != it_end)
    {
        cost = it_connection->computeCost();
        cout << "connects -> " << it_connection->getNextPlace() << " : "  << it_connection->getDesc() << ", cost = " << cost << endl;
        if (cost < minCost)
        {
            minCost = cost;
            winner = &(*it_connection);
        }
        it_connection++;	
    }

    cout << "selected -> " << winner->getNextPlace() << endl;
    return winner->getID();
}