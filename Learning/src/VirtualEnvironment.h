#ifndef __VITUALENVIRONMENT_H
#define __VIRTUALENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Environment.h"
#include "Connection.h"

namespace sam 
{
class VirtualEnvironment
{
private:
    Environment oEnvironment;
    int placeNow;
    
public:
    VirtualEnvironment();
    void build6RoomTest();
    std::vector<Connection>& getPresentConnections();
    void crossConnection(int connectionID);
    
    int getPlaceNow() const;
    void setPlaceNow(int);  

};
}

#endif
