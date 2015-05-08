#ifndef __CONNECTION_H
#define __CONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "Database.h"

namespace sam
{
class Connection
{
private:
    int ID;
    std::string desc;
    int environmentID;
    int placeID;
    int nextPlace;
    int length;
    int slope;
    int abruptness;
    
public:
    Connection();
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();

    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
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
}

#endif
