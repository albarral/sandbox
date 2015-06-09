/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Place.h"
#include "Environment.h"

namespace sam 
{
Place::Place() 
{
    ID = 0;
    desc = "";
    environmentID = 0;
    reward = 0;
}

void Place::addConnection(Connection& oConnection)
{
    // connection ID is assigned automatically
    oConnection.setID(listConnections.size());
    listConnections.push_back(oConnection);
}

void Place::loadFromMemo(Database* pDatabase, sql::Connection *con)
{
    std::string sel = "SELECT * FROM TAB_PLACES WHERE envID = " + std::to_string(environmentID)
            + " AND placeID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
      
    while (res -> next())
    {
        desc = res -> getString("description");
        reward = res -> getDouble("reward");
    }
    
    connectionsFromMemo(pDatabase, con);
    loadConnections(pDatabase, con);
}

void Place::storeInMemo(Database* pDatabase, sql::Connection *con)
{
    std::string insertDB = "INSERT INTO TAB_PLACES (placeID, description, envID, reward) VALUES ("
            + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(environmentID)
            + ", " + std::to_string(reward) +")";    
    pDatabase->update(insertDB, con);
    
    storeConnections(pDatabase, con);
}

void Place::upDateInMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_PLACES SET description = ' " + desc + " ' ,reward = " + std::to_string(reward) 
    + " WHERE placeID = " + std::to_string(ID) + " AND envID= " + std::to_string(environmentID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Place::deleteFromMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_PLACES WHERE placeID= "+ std::to_string(ID);
            + " AND envID= " + std::to_string(environmentID);
    pDatabase->update(deleteDB, con);    
    con->commit();
    pDatabase->closeConnectionDB();
}

void Place::connectionsFromMemo(Database* pDatabase, sql::Connection *con)
{
    std::string sel = "SELECT connID FROM TAB_CONNECTIONS WHERE envID = " + std::to_string(environmentID)
            + " AND placeID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
    
    while (res -> next())
    {
        Connection oConnection;
        oConnection.setEnvironmentID(environmentID);
        oConnection.setPlaceID(ID);
        int id = res -> getInt("connID");
        oConnection.setID(id);
        addConnection(oConnection);
    }
}

void Place::loadConnections(Database* pDatabase, sql::Connection *con)
{
    std::vector<Connection>::iterator it_connetion = listConnections.begin();
    std::vector<Connection>::iterator it_end = listConnections.end();
    while (it_connetion != it_end)
    {
        it_connetion->loadFromMemo(pDatabase, con);
        it_connetion++;	
    }
}

void Place::storeConnections(Database* pDatabase, sql::Connection *con)
{
    std::vector<Connection>::iterator it_connetion = listConnections.begin();
    std::vector<Connection>::iterator it_end = listConnections.end();
    while (it_connetion != it_end)
    {
        it_connetion->storeInMemo(pDatabase, con);
        it_connetion++;	
    }
}

std::string Place::showData()
{
    std::string data = "> place " + std::to_string(ID) + ": " + desc;    
    return data;
}

}