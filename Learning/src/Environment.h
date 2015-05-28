#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

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
    
    int getID() {return ID;};
    void setID(int id) {ID = id;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string de) {desc = de;};
    
    int getType() {return type;};
    void setType(int ty) {type = ty;};
    
    std::vector<Place>& getListPlaces() {return listPlaces;};
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
