/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Place.h"

namespace sam 
{
Place::Place() 
{
    ID = 0;
    environmentID = 0;
}

void Place::addConnection(Connection& oConnection)
{
    // connection ID is assigned automatically
    oConnection.setID(listConnections.size());
    listConnections.push_back(oConnection);
}

void Place::loadFromMemo()
{}

void Place::storeInMemo()
{
    Database oDatabase;
    
    std::string insertDB = "INSERT INTO TAB_PLACES (ID, desc, environmentID) VALUES ("
            + std::to_string(ID) + ", " + desc + ", " + std::to_string(environmentID) + ")";    
    oDatabase.insertToDB(insertDB);
}

void Place::upDateInMemo()
{
    Database oDatabase;
}

void Place::deleteFromMemo()
{
    Database oDatabase;
    std::string deleteDB = "DELETE FROM TAB_PLACES WHERE ID= "+ std::to_string(ID);
    oDatabase.deleteDB(deleteDB);    
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