#ifndef __SAM_LEARN_PLACE_H
#define __SAM_LEARN_PLACE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Connection.h"
#include "sam/utilsDB/Database.h"

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
    void loadFromMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void storeInMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void upDateInMemo(utilsDB::Database* pDatabase);
    void deleteFromMemo(utilsDB::Database* pDatabase);
    void storeQ(utilsDB::Database* pDatabase, sql::Connection* con);
    
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
    void connectionsFromMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void loadConnections(utilsDB::Database* pDatabase, sql::Connection* con);
    void storeConnections(utilsDB::Database* pDatabase, sql::Connection* con);

};
}

#endif
