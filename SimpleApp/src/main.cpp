/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 
#include <iostream> // for cout
#include <vector>

#include "Click.h"

using namespace std;

void testClick(int secs);
void testClick2();

// main program
int main(int argc, char** argv) 
{
    cout << "first test ..." << endl;
    
    testClick(3); 
    //testClick(4); 

    cout << endl << "second test ..." << endl;

    testClick2();
    
    cout << endl << "end of tests" << endl;

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
