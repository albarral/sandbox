
/* 
 * 
 * Author: Ainoa Millán
 *
 */

//#include <iostream>
#include <string>
#ifndef __CONNECTION_H
#define __CONNECTION_H

//#include "opencv2/core/core.hpp"

using namespace std;

class Connection
{
private:
    int ID;
    string desc;
    int environmentID;
    int placeID;
    int nextPlace;
    int length;
    int slope;
    int abruptness;
    
public:
    Connection();
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getEnvironmentID() const;
    void setEnvironmentID(int);
    
    int getPlaceID() const;
    void setPlaceID(int);
    
    int getNextPlace() const;
    void setNextPlace(int);
    
    int getLength() const;
    void setLength(int);
    
    int getSlope() const;
    void setSlope(int);
    
    int getAbruptness() const;
    void setAbruptness(int);
   
    float computeCost();
    
    void showData();
};

#endif
