/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Place.h"
#include "Environment.h"

namespace sam 
{
Place::Place() 
{
    ID = 0;
    desc = "default";
    environmentID = 0;
}

void Place::addConnection(Connection& oConnection)
{
    // connection ID is assigned automatically
    oConnection.setID(listConnections.size());
    listConnections.push_back(oConnection);
}

void Place::loadFromMemo(Database* pDatabase, sql::Connection *con)
{
    std::string select = "SELECT * FROM TAB_PLACES";
    sql::ResultSet *res = pDatabase->selectFrom(select, con);
    Place oPlace;
    
    while (res -> next())
    {
//        std::cout <<"Places" << std::endl;
        oPlace.ID = res -> getInt("ID");
        oPlace.desc = res -> getString("description");
        oPlace.environmentID = res -> getInt("environmentID");
//        std::cout <<ID << std::endl << desc << std::endl << environmentID << std::endl;
        
        Environment oEnvironment;
        oEnvironment.addPlace(oPlace);
    }
    
    Connection oConnection;
    oConnection.loadFromMemo(pDatabase, con);
}

void Place::storeInMemo(Database* pDatabase, sql::Connection *con)
{
    std::string insertDB = "INSERT INTO TAB_PLACES (ID, description, environmentID) VALUES ("
            + std::to_string(ID) + ", " + desc + ", " + std::to_string(environmentID) + ")";    
    pDatabase->insertToDB(insertDB, con);
    
    storeConnections(pDatabase, con);
}

void Place::upDateInMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_PLACES SET description = " + desc + " WHERE ID = " + std::to_string(ID)
            + " AND environmentID= " + std::to_string(environmentID);
    pDatabase->updateDB(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Place::deleteFromMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_PLACES WHERE ID= "+ std::to_string(ID);
            + " AND environmentID= " + std::to_string(environmentID);
    pDatabase->deleteDB(deleteDB, con);    
    con->commit();
    pDatabase->closeConnectionDB();
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

int Place::getID() const
{ 
    return ID; 
}

void Place::setID(int id)
{
    ID = id;
}    

std::string Place::getDesc() const
{ 
    return desc; 
}

void Place::setDesc(std::string de)
{
    desc = de;
}

int Place::getEnvironmentID() const
{ 
    return environmentID; 
}

void Place::setEnvironmentID(int eID)
{
    environmentID = eID;
}   

std::vector<Connection>& Place::getListConnections()
{
    return listConnections;
}

void Place::showData()
{
    std::cout << "place " << ID << std::endl;
    std::cout << "- connections = " << listConnections.size() << std::endl;    
}

}