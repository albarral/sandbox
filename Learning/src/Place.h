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
    void loadFromMemo(Database* pDatabase, sql::Connection *con);
    void storeInMemo(Database* pDatabase, sql::Connection *con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    
    int getID() {return ID;}; 
    void setID(int id) {ID = id;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string de) {desc = de;};
    
    int getEnvironmentID() {return environmentID;};
    void setEnvironmentID(int eID) {environmentID = eID;};
    
    std::vector<Connection>& getListConnections() {return listConnections;};
    
    float getReward() {return reward;};
    void setReward(float rwrd) {reward = rwrd;};

    std::string showData();
   
private:
    void connectionsFromMemo(Database* pDatabase, sql::Connection *con);
    void loadConnections(Database* pDatabase, sql::Connection *con);
    void storeConnections(Database* pDatabase, sql::Connection *con);

};
}

#endif
