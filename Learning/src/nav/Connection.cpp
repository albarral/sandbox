/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Connection.h"
#include "Place.h"
#include "ConnectionType.h"

namespace sam
{
Connection::Connection() 
{
    ID = 0;
    desc = "";
    environmentID = 0;
    placeID = 0;
    nextPlace = 0;
    length = 0;
    slope = 0;
    abruptness = 0;
    Q = 0; 
}

void Connection::set(int placeID, int nextPlace, int type)
{    
    this->placeID = placeID;
    this->nextPlace = nextPlace;
          
    ConnectionType oType;
    oType.set(type);
    this->desc = oType.getDesc();    
    this->length = oType.getLength();
    this->slope = oType.getSlope();
    this->abruptness = oType.getAbruptness();
}

void Connection::loadFromMemo(utils::Database* pDatabase, sql::Connection* con)
{
    std::string sel = "SELECT * FROM TAB_CONNECTIONS WHERE envID = " + std::to_string(environmentID)
            + " AND placeID = " + std::to_string(placeID) + " AND connID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
    
    while (res->next())
    {
        desc = res->getString("description");
        nextPlace = res->getInt("nextPlace");
        length = res->getInt("length");
        slope = res->getInt("slope");
        abruptness = res->getInt("abruptness");  
        Q = res->getDouble("Q");
    }
}

void Connection::storeInMemo(utils::Database* pDatabase, sql::Connection* con)
{
    std::string insert = "INSERT INTO TAB_CONNECTIONS (connID, description, envID, placeID, nextPlace, length, "
            "slope, abruptness, Q) VALUES (" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(environmentID) 
            + ", " + std::to_string(placeID) + ", " + std::to_string(nextPlace) + ", " + std::to_string(length)
            + ", " + std::to_string(slope) + ", " + std::to_string(abruptness) + ", " + std::to_string(Q) +")";   
    pDatabase->update(insert, con);
}

void Connection::upDateInMemo(utils::Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_CONNECTIONS SET description= ' " + desc +
            " ' nextPlace = " + std::to_string(nextPlace) + ", length = " + std::to_string(length) + ", slope = " + 
            std::to_string(slope) + ", abruptness = " + std::to_string(abruptness) + ", Q = " + std::to_string(Q) 
            + " WHERE connID = " + std::to_string(ID) + " AND envID= " + std::to_string(environmentID)
            + " AND placeID= " + std::to_string(placeID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Connection::deleteFromMemo(utils::Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_CONNECTIONS WHERE connID= " + std::to_string(ID)
            + " AND envID= " + std::to_string(environmentID) + " AND placeID= " + std::to_string(placeID);
    pDatabase->update(deleteDB, con);   
    con->commit();
    pDatabase->closeConnectionDB();
}

void Connection::storeQ(utils::Database* pDatabase, sql::Connection* con)
{
    std::string storeQ = "UPDATE TAB_CONNECTIONS SET Q= " + std::to_string(Q) + " WHERE connID= " + std::to_string(ID)
            + " AND envID= " + std::to_string(environmentID) + " AND placeID= " + std::to_string(placeID);   
    pDatabase->update(storeQ, con);
}

// computes the cost of traversing the connection
float Connection::computeCost()
{
    return (length * (1 + ((float)slope/30)) * (1 + ((float)abruptness/10)) );
}

std::string Connection::showData()
{
    std::string data = ">> connection " + std::to_string(ID) + ": " + std::to_string(placeID) + "->" + std::to_string(nextPlace) + ", " + desc;
    return data;
}

}