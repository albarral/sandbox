#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Place.h"
#include "Database.h"

namespace sam 
{
class Environment
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<Place> listPlaces;
    Database* pDatabase;
    
public:
    Environment();
    void addPlace(Place& oPlace);
    
    void setDatabase(Database& oDatabase) {pDatabase = &oDatabase;}
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();
    
    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
    int getType() const;
    void setType(int);
    
    std::vector<Place>& getListPlaces();

private:
    void placesFromMemo(sql::Connection *con);
    void loadPlaces(sql::Connection *con);
    void storePlaces(sql::Connection *con);
    
};
}

#endif
