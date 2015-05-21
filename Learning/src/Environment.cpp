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
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string select = "SELECT * FROM TAB_ENVIRONMENTS";
    sql::ResultSet *res = pDatabase->selectFrom(select, con);
    Environment oEnvironment;
    
    while (res -> next())
    {
        std::cout <<"Environment: "<< std::endl;
        ID = res -> getInt("ID");
        desc = res -> getString("description");
        type = res -> getInt("type");
//        std::cout <<ID << std::endl << desc << std::endl << type << std::endl;
    }
    
    Place oPlace;
    oPlace.loadFromMemo(pDatabase, con);
    pDatabase->closeConnectionDB();
}

void Environment::storeInMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string insert = "INSERT INTO TAB_ENVIRONMENTS (ID, description, type) VALUES "
            "(" + std::to_string(ID) + ", " + desc + ", " + std::to_string(type) + ")";    
    pDatabase->insertToDB(insert, con);
    
    storePlaces(con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Environment::upDateInMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_ENVIRONMENTS SET description = " + desc + ", type = " 
            + std::to_string(type) + " WHERE ID= " + std::to_string(ID);
    pDatabase->updateDB(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Environment::deleteFromMemo()
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_ENVIRONMENTS WHERE ID= " + std::to_string(ID);
    pDatabase->deleteDB(deleteDB, con);  
    con->commit();
    pDatabase->closeConnectionDB();
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