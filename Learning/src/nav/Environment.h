#ifndef __SAM_LEARN_ENVIRONMENT_H
#define __SAM_LEARN_ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Place.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
class Environment
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<Place> listPlaces;
    utilsDB::Database* pDatabase;
    
public:
    Environment();
    
    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getType() {return type;};
    void setType(int value) {type = value;};
    
    std::vector<Place>& getListPlaces() {return listPlaces;};
    void addPlace(Place& oPlace);

    void setDatabase(utilsDB::Database& oDatabase) {pDatabase = &oDatabase;}
    
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();
    void storeQ();
    void reset();

    std::string showData();

private:
    void placesFromMemo(sql::Connection* con);
    void loadPlaces(sql::Connection* con);
    void storePlaces(sql::Connection* con);
    
};
}

#endif
