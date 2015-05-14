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
}

void Environment::loadFromMemo()
{}

void Environment::storeInMemo()
{
    std::string insert = "INSERT INTO TAB_ENVIRONMENTS (ID, description, type) VALUES "
            "(" + std::to_string(ID) + ", " + desc + ", " + std::to_string(type) + ")";    
    pDatabase->insertToDB(insert);
    
    storePlaces();
}

void Environment::upDateInMemo()
{
    std::string update = "UPDATE TAB_ENVIRONMENTS SET description = " + desc + ", type = " 
            + std::to_string(type) + " WHERE ID= " + std::to_string(ID);
    pDatabase->updateDB(update);
}

void Environment::deleteFromMemo()
{
    std::string deleteDB = "DELETE FROM TAB_ENVIRONMENTS WHERE ID= " + std::to_string(ID);
    pDatabase->deleteDB(deleteDB);    
}

void Environment::storePlaces()
{
    std::vector<Place>::iterator it_place = listPlaces.begin();
    std::vector<Place>::iterator it_end = listPlaces.end();
    while (it_place != it_end)
    {
        it_place->storeInMemo(pDatabase);
        it_place++;	
    }
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