/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include "Place.h"

Place::Place() 
{
    ID = 0;
    environmentID = 0;
}

void Place::addConnection(Connection& oConnection)
{
    listConnections.push_back(oConnection);
}

void Place::loadFromMemo()
{}

int Place::getID() const
{ 
    return ID; 
}

void Place::setID(int id)
{
    ID = id;
}    

string Place::getDesc() const
{ 
    return desc; 
}

void Place::setDesc(string de)
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

vector<Connection> Place::getListConnections() const
{
    return listConnections;
}

void Place::setListConnections(vector<Connection> connections)
{
    listConnections = connections;
}
