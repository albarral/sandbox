#ifndef __SAM_PLACE_H
#define __SAM_PLACE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Connection.h"
#include "sam/utils/Database.h"

namespace sam 
{
class Place
{
private:
    int ID;
    std::string desc;
    int environmentID;
    std::vector<Connection> listConnections;
    float reward; //TEMPORAL!!!! (Will go only in State)
    
public:
    Place();
    void addConnection(Connection& oConnection);
    void loadFromMemo(Database* pDatabase, sql::Connection* con);
    void storeInMemo(Database* pDatabase, sql::Connection* con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    void storeQ(Database* pDatabase, sql::Connection* con);
    
    int getID() {return ID;}; 
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getEnvironmentID() {return environmentID;};
    void setEnvironmentID(int value) {environmentID = value;};
    
    std::vector<Connection>& getListConnections() {return listConnections;};
    
    float getReward() {return reward;};
    void setReward(float value) {reward = value;};

    std::string showData();
   
private:
    void connectionsFromMemo(Database* pDatabase, sql::Connection* con);
    void loadConnections(Database* pDatabase, sql::Connection* con);
    void storeConnections(Database* pDatabase, sql::Connection* con);

};
}

#endif
