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
#include "Environment.h"
#include "Place.h"
#include "Connection.h"
#include "Task.h"
#include "State.h"
#include "Transition.h"
#include "VirtualEnvironment.h"

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
    
    VirtualEnvironment oVirtualEnvironment;
    oVirtualEnvironment.build6RoomTest();
    oVirtualEnvironment.setPlaceNow(5);
    int conID = oVirtualEnvironment.getConnections();
    cout<< "Returned connection: " <<conID<< endl;
    oVirtualEnvironment.crossConnection(conID);
    int plcnw = oVirtualEnvironment.getPlaceNow();
    cout<< "Next place: " << plcnw<<endl;
    
    return;
}