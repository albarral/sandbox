#ifndef __VITUALENVIRONMENT_H
#define __VIRTUALENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Environment.h"
#include "Connection.h"
#include "sam/utils/Database.h"

namespace sam 
{
class VirtualEnvironment
{
private:
    Environment oEnvironment;
    Database oDatabase;
    int placeNow;
    
public:
    VirtualEnvironment();

    void init(int ID);

    int getPlaceNow() const;
    void setPlaceNow(int);  
    std::vector<Connection>& getPresentConnections();    
    void crossConnection(int connectionID);
    
private:
    void create();
    void storeInMemo();
    void loadFromMemo();
    
    int getPlaceNow() const {return placeNow;};
    void setPlaceNow(int pNow) {placeNow = pNow;};

    void build6RoomTest();
    void build7RoomTest();
    void build8RoomTest();

};
}

#endif
