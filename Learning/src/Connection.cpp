/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Connection.h"
#include "Place.h"

namespace sam
{
Connection::Connection() 
{
    ID = 0;
    desc = "default";
    environmentID = 0;
    placeID = 0;
    nextPlace = 0;
    length = 0;
    slope = 0;
    abruptness = 0;
}

void Connection::loadFromMemo(Database* pDatabase, sql::Connection *con)
{
    std::string sel = "SELECT * FROM TAB_CONNECTIONS WHERE envID = " + std::to_string(environmentID)
            + "AND placeID = " + std::to_string(placeID) + " AND connID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
    
    while (res -> next())
    {
        std::cout <<"Connection: "<< std::endl;
        desc = res -> getString("description");
        nextPlace = res -> getInt("nextPlace");
        length = res -> getInt("length");
        slope = res -> getInt("slope");
        abruptness = res -> getInt("abruptness");
        std::cout <<ID << std::endl << desc << std::endl << environmentID << std::endl << placeID<< std::endl 
                << nextPlace << std::endl << length << std::endl << slope << std::endl << abruptness << std::endl;       
    }
}

void Connection::storeInMemo(Database* pDatabase, sql::Connection *con)
{
    std::string insert = "INSERT INTO TAB_CONNECTIONS (connID, description, envID, placeID, nextPlace, length, "
            "slope, abruptness) VALUES (" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(environmentID) 
            + ", " + std::to_string(placeID) + ", " + std::to_string(nextPlace) + ", " + std::to_string(length)
            + ", " + std::to_string(slope) + ", " + std::to_string(abruptness) + ")";   
    pDatabase->update(insert, con);
}

void Connection::upDateInMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_CONNECTIONS SET description= ' " + desc +
            " ' nextPlace = " + std::to_string(nextPlace) + ", length = " + std::to_string(length) + ", slope = " + 
            std::to_string(slope) + ", abruptness = " + std::to_string(abruptness) + " WHERE connID = " + std::to_string(ID)
            + " AND envID= " + std::to_string(environmentID) + " AND placeID= " + std::to_string(placeID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Connection::deleteFromMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_CONNECTIONS WHERE connID= " + std::to_string(ID);
            + " AND envID= " + std::to_string(environmentID) + " AND placeID= " + std::to_string(placeID);
    pDatabase->update(deleteDB, con);   
    con->commit();
    pDatabase->closeConnectionDB();
}

int Connection::getID() const
{ 
    return ID; 
}

void Connection::setID(int id)
{
    ID = id;
}    

std::string Connection::getDesc() const
{ 
    return desc; 
}

void Connection::setDesc(std::string de)
{
    desc = de;
}

int Connection::getEnvironmentID() const
{ 
    return environmentID; 
}

void Connection::setEnvironmentID(int eID)
{
    environmentID = eID;
}

int Connection::getPlaceID() const
{ 
    return placeID; 
}

void Connection::setPlaceID(int pID)
{
    placeID = pID;
}   

int Connection::getNextPlace() const
{ 
    return nextPlace; 
}

void Connection::setNextPlace(int nxPlc)
{
    nextPlace = nxPlc;
} 

int Connection::getLength() const
{ 
    return length; 
}

void Connection::setLength(int leng)
{
    length = leng;
} 

int Connection::getSlope() const
{ 
    return slope; 
}

void Connection::setSlope(int slp)
{
    slope = slp;
} 

int Connection::getAbruptness() const
{ 
    return abruptness; 
}

void Connection::setAbruptness(int abtns)
{
    abruptness = abtns;
} 

// computes the cost of traversing the connection
float Connection::computeCost()
{
    return (length * slope * abruptness);
}

void Connection::showData()
{
    std::cout << "connection " << ID << ": " << placeID << " -> " << nextPlace << std::endl;

}

}