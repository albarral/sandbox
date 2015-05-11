/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Environment.h"

namespace sam 
{
Environment::Environment() 
{
    ID = 0;
    desc = "default";
    type= 0;
}

void Environment::addPlace(Place& oPlace)
{
    listPlaces.push_back(oPlace);
    oPlace.storeInMemo();
}

void Environment::loadFromMemo()
{}

void Environment::storeInMemo()
{
    Database oDatabase;
    
    std::string insert = "INSERT INTO TAB_ENVIRONMENTS VALUES "
            "(" + std::to_string(ID) + ", " + desc + ", " + std::to_string(type) + ")";    
    oDatabase.insertToDB(insert);
}

void Environment::upDateInMemo()
{
    Database oDatabase;
    std::string update = "UPDATE TAB_ENVIRONMENTS SET description = " + desc + ", type = " 
            + std::to_string(type) + " WHERE ID= " + std::to_string(ID);
    oDatabase.upDateDB(update);
}

void Environment::deleteFromMemo()
{
    Database oDatabase;
    std::string deleteDB = "DELETE FROM TAB_ENVIRONMENTS WHERE ID= " + std::to_string(ID);
    oDatabase.deleteDB(deleteDB);    
}

int Environment::getID() const
{ 
    return ID; 
}

void Environment::setID(int id)
{
    ID = id;
}    

std::string Environment::getDesc() const
{ 
    return desc; 
}

void Environment::setDesc(std::string de)
{
    desc = de;
}

int Environment::getType() const
{ 
    return type; 
}

void Environment::setType(int ty)
{
    type = ty;
}   

std::vector<Place>& Environment::getListPlaces()
{
    return listPlaces;
}

}