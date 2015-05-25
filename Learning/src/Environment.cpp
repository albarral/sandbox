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
    ID = 1;
    desc = "default";
    type= 0;
}

void Environment::addPlace(Place& oPlace)
{
    listPlaces.push_back(oPlace);
}

void Environment::loadFromMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string sel = "SELECT * FROM TAB_ENVIRONMENTS WHERE envID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
       
    while (res -> next())
    {
        std::cout <<"Environment: "<< std::endl;
        ID = res -> getInt("envID");
        desc = res -> getString("description");
        type = res -> getInt("type");
        std::cout <<ID << std::endl << desc << std::endl << type << std::endl;
    }
    
    placesFromMemo(con);
    loadPlaces(con);
    
    pDatabase->closeConnectionDB();
}

void Environment::storeInMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string insert = "INSERT INTO TAB_ENVIRONMENTS (envID, description, type) VALUES "
            "(" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(type) + ")";    
    pDatabase->update(insert, con);
    
    storePlaces(con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Environment::upDateInMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_ENVIRONMENTS SET description = ' " + desc + " ', type = " 
            + std::to_string(type) + " WHERE envID= " + std::to_string(ID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Environment::deleteFromMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_ENVIRONMENTS WHERE envID= " + std::to_string(ID);
    pDatabase->update(deleteDB, con);  
    con->commit();
    pDatabase->closeConnectionDB();
}

void Environment::placesFromMemo(sql::Connection *con)
{
    std::string sel = "SELECT placeID FROM TAB_PLACES WHERE envID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
    
    while (res -> next())
    {
        Place oPlace;
        oPlace.setEnvironmentID(ID);
        int id = res -> getInt("placeID");
        oPlace.setID(id);
        addPlace(oPlace);
    }    
}

void Environment::loadPlaces(sql::Connection *con)
{
    std::vector<Place>::iterator it_place = listPlaces.begin();
    std::vector<Place>::iterator it_end = listPlaces.end();
    while (it_place != it_end)
    {
        it_place->loadFromMemo(pDatabase, con);
        it_place++;
    }
}

void Environment::storePlaces(sql::Connection *con)
{
    std::vector<Place>::iterator it_place = listPlaces.begin();
    std::vector<Place>::iterator it_end = listPlaces.end();
    while (it_place != it_end)
    {
        it_place->storeInMemo(pDatabase, con);
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