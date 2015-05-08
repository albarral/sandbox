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
    type= 0;
}

void Environment::addPlace(Place& oPlace)
{
    listPlaces.push_back(oPlace);
}

void Environment::loadFromMemo()
{}

void Environment::storeInMemo()
{
    Database oDatabase;
    
    std::string insert = "INSERT INTO TAB_ENVIRONMENTS (ID, desc, type) VALUES "
            "(" + ID + ", " + desc + ", " + type + ")";    
    oDatabase.insertToDB(insert);
    
    std::string deleteDB = "DELETE FROM TAB_ENVIRONMENTS WHERE ID= " + ID +";
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