#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Place.h"

namespace sam 
{
class Environment
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<Place> listPlaces;
    
public:
    Environment();
    void addPlace(Place& oPlace);
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
    int getType() const;
    void setType(int);
    
    std::vector<Place>& getListPlaces();

};
}

#endif
