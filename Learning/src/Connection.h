#ifndef __SAM_CONNECTION_H
#define __SAM_CONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/utils/Database.h"

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
    float Q; //TEMPORAL!!!!  (Will go only in Transition)
    
public:
    Connection();
        
    void loadFromMemo(Database* pDatabase, sql::Connection* con);
    void storeInMemo(Database* pDatabase, sql::Connection* con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    void storeQ(Database* pDatabase, sql::Connection* con);

    // sets 6 members at a time (type is a ConnectionType predefined type)
    void set(int placeID, int nextPlace, int type);

    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getEnvironmentID() {return environmentID;};
    void setEnvironmentID(int value) {environmentID = value;};
    
    int getPlaceID() {return placeID;};
    void setPlaceID(int value) {placeID = value;};
    
    int getNextPlace() {return nextPlace;};
    void setNextPlace(int value) {nextPlace = value;};
    
    int getLength() {return length;};
    void setLength(int value) {length = value;};
    
    int getSlope() {return slope;};
    void setSlope(int value) {slope = value;};
    
    int getAbruptness() {return abruptness;};
    void setAbruptness(int value) {abruptness = value;}; 
    
    float getQ() {return Q;};
    void setQ(float value) {Q = value;};

    float computeCost();
    
    std::string showData();    
};
}

#endif
