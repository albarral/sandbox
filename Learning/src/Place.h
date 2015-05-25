#ifndef __PLACE_H
#define __PLACE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Connection.h"
#include "Database.h"

namespace sam 
{
class Place
{
private:
    int ID;
    std::string desc;
    int environmentID;
    std::vector<Connection> listConnections;
    
public:
    Place();
    void addConnection(Connection& oConnection);
    void loadFromMemo(Database* pDatabase, sql::Connection *con);
    void storeInMemo(Database* pDatabase, sql::Connection *con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    
    int getID() const; 
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
    int getEnvironmentID() const;
    void setEnvironmentID(int);
    
    std::vector<Connection>& getListConnections();

    void showData();
   
private:
    void connectionsFromMemo(Database* pDatabase, sql::Connection *con);
    void loadConnections(Database* pDatabase, sql::Connection *con);
    void storeConnections(Database* pDatabase, sql::Connection *con);

};
}

#endif
