/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 
#include <iostream> // for cout
#include <vector>
#include "opencv2/core/core.hpp"

#include "Click.h"
#include "distance.h"
#include "navigation/Connection.h"
#include "navigation/Place.h"
#include "navigation/Environment.h"

using namespace std;

void testClick(int secs);
void testClick2();
void testLib1();
void testEnvironment();

// main program
int main(int argc, char** argv) 
{
    cout << endl << "tests init" << endl;

    //cout << "test click ..." << endl;    
    //testClick(3); 

    //cout << endl << "test lib ..." << endl;
    //testLib1();

    cout << endl << "test testEnvironment ..." << endl;
    testEnvironment();
    
    cout << endl << "tests finished" << endl;

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
    sam::Environment oEnvironment;
    sam::Place oPlace0, oPlace1, oPlace2;
    sam::Connection oConnection;

    oEnvironment.setID(1);
    oPlace0.setID(0);    
    oPlace1.setID(1);    
    oPlace2.setID(2);    

    // 0 -> 1
    oConnection.setID(1);
    oConnection.setPlace(0);
    oConnection.setNextPlace(1);    
    oPlace0.addConnection(oConnection);
    // 0 -> 2
    oConnection.setID(2);
    oConnection.setNextPlace(2);    
    oPlace0.addConnection(oConnection);

    // rest of connection should be made for places 2 & 3 ...
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    
    // get Connections
    int placeNow = 0;
    std::vector<int> listConnectionIDs; 
    
    // prepare the list iterator
    sam::Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    std::vector<sam::Connection>::iterator it_connections = mPlaceNow.getListConnections().begin();
    std::vector<sam::Connection>::iterator it_end = mPlaceNow.getListConnections().end();
    // walk the list getting the connection IDs
    while (it_connections != it_end)
    {
        int connectionID = it_connections->getID();
        listConnectionIDs.push_back(connectionID);
        it_connections++;	
    }
    
    // return listConnectionIDs;   
}