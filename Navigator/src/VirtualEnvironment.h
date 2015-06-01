#ifndef __SAM_VIRTUAL_ENVIRONMENT_H
#define __SAM_VIRTUAL_ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "Environment.h"
#include "Connection.h"
#include "sam/utils/Database.h"

namespace sam 
{
class VirtualEnvironment
{
public:
    // environments
    enum eType
    {
         eENV_6ROOM, 
         eENV_7ROOM, 
         eENV_8ROOM, 
         eENV_UNKNOWN, 
    };
    
private:
    static log4cxx::LoggerPtr logger;
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

    // shows brief description of given environment
    void describeEnvironment(Environment* pEnvironment);
    // shows brief description of given place
    void describePlace(Place* pPlace);
    
    void build6RoomTest();
    void build7RoomTest();
    void build8RoomTest();

};
}

#endif
