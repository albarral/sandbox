/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include "Environment.h"

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

int Environment::getID() const
{ 
    return ID; 
}

void Environment::setID(int id)
{
    ID = id;
}    

string Environment::getDesc() const
{ 
    return desc; 
}

void Environment::setDesc(string de)
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

