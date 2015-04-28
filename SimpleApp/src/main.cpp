/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 
#include <iostream> // for cout
#include <vector>
#include "opencv2/core/core.hpp" // for cv::Vec2i

#include "Click.h"
#include "distance.h"
// Learning classes
#include "Connection.h"
#include "VirtualEnvironment.h"

using namespace std;

void testClick(int secs);
void testClick2();
void testLib1();
void testEnvironment();
int selectConnection(std::vector<sam::Connection>& listConnections);

// main program
int main(int argc, char** argv) 
{
    //cout << "test click ..." << endl;    
    //testClick(3); 

    //cout << endl << "test lib ..." << endl;
    //testLib1();

    cout << endl << "test testEnvironment ..." << endl;
    testEnvironment();
      
    sleep(1);   // not needed
    
    return 0;
}

// Usage of Click class for measurement of time intervals
void testClick(int secs) 
{                
    goon::Click oClick;
    
    cout << "wait " << secs << " secs" << endl;

    oClick.start();            
    sleep(secs);    
    oClick.stop();

    cout << "ellapsed time = " << oClick.getMillis() << " ms" << endl;
    
    return;
}

// Usage of vectors (a type of STL classes). 
void testClick2() 
{                
    // set vector of waiting times
    vector<int> list;
    list.push_back(2); 
    //list.push_back(3);
    //list.push_back(1);
    
    // walk the list 
    vector<int>::iterator iter;        
    for (iter = list.begin(); iter != list.end(); iter++)
    {
        testClick(*iter);
    }    
    
    return;
}


void testLib1() 
{                
    cv::Vec2i pos1 = {1, 1};
    cv::Vec2i pos2 = {10, 10};
    
    int dist = sqrt(Distance::getEuclidean3s(pos1, pos2));

    cout << "distance = " << dist << endl;
    
    return;
}

void testEnvironment()
{
    int nextConnectionID;
    
    sam::VirtualEnvironment oVirtualEnvironment;
    oVirtualEnvironment.build6RoomTest();
    oVirtualEnvironment.setPlaceNow(5);
    cout << "Initial place: " << oVirtualEnvironment.getPlaceNow() <<endl;
    
    for (int i=0; i<3; i++)
    {
        std::vector<sam::Connection>& listConnections = oVirtualEnvironment.getPresentConnections();
        nextConnectionID = selectConnection(listConnections);
        cout << "Selected connection: " << nextConnectionID << endl;
        oVirtualEnvironment.crossConnection(nextConnectionID);    
        cout << "New place: " << oVirtualEnvironment.getPlaceNow() <<endl;
    }
    
//    int conID = oVirtualEnvironment.getConnections();
//    cout<< "Returned connection: " <<conID<< endl;
//    oVirtualEnvironment.crossConnection(conID);
//    int plcnw = oVirtualEnvironment.getPlaceNow();
//    cout<< "Next place: " << plcnw<<endl;
    
    return;
}

// selects the connection with the lowest cost to traverse
int selectConnection(std::vector<sam::Connection>& listConnections)
{        
    vector<sam::Connection>::iterator it_connection = listConnections.begin();
    vector<sam::Connection>::iterator it_end = listConnections.end();
    float cost, minCost = 1000;
    int connectionID, winner=-1;
    // walk the list of connections and tracks the one with lowest cost
    while (it_connection != it_end)
    {
        cost = it_connection->computeCost();
        if (cost < minCost)
        {
            minCost = cost;
            winner = it_connection->getID();
            it_connection->showData();
        }
        it_connection++;	
    }

    return winner;
}