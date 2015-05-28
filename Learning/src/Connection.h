#ifndef __CONNECTION_H
#define __CONNECTION_H

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
    
public:
    Connection();
        
    void loadFromMemo(Database* pDatabase, sql::Connection *con);
    void storeInMemo(Database* pDatabase, sql::Connection *con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);

    // sets 6 members at a time (type is a ConnectionType predefined type)
    void set(int placeID, int nextPlace, int type);

    int getID() {return ID;};
    void setID(int id) {ID = id;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string de) {desc = de;};
    
    int getEnvironmentID() {return environmentID;};
    void setEnvironmentID(int eID) {environmentID = eID;};
    
    int getPlaceID() {return placeID;};
    void setPlaceID(int pID) {placeID = pID;};
    
    int getNextPlace() {return nextPlace;};
    void setNextPlace(int nxPlc) {nextPlace = nxPlc;};
    
    int getLength() {return length;};
    void setLength(int leng) {length = leng;};
    
    int getSlope() {return slope;};
    void setSlope(int slp) {slope = slp;};
    
    int getAbruptness() {return abruptness;};
    void setAbruptness(int abtns) {abruptness = abtns;}; 

    float computeCost();
    
    void showData();    
};
}

#endif
