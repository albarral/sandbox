#ifndef __SAM_ENVIRONMENT_H
#define __SAM_ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Place.h"
#include "sam/utils/Database.h"

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
    
    int getID();
    void setID(int);
    
    std::string getDesc();
    void setDesc(std::string);
    
    int getType();
    void setType(int);
    
    std::vector<Place>& getListPlaces();
    void addPlace(Place& oPlace);

    void setDatabase(Database& oDatabase) {pDatabase = &oDatabase;}
    
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();
    void reset();

private:
    void placesFromMemo(sql::Connection *con);
    void loadPlaces(sql::Connection *con);
    void storePlaces(sql::Connection *con);
    
};
}

#endif
