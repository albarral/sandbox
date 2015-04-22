
/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include <iostream>
#include <string>
#ifndef __VITUALENVIRONMENT_H
#define __VIRTUALENVIRONMENT_H

#include "Environment.h"
#include "Place.h"
#include "Connection.h"
#include "opencv2/core/core.hpp"

using namespace std;

class VirtualEnvironment
{
private:
    Environment oEnvironment;
    int placeNow;
    
public:
    VirtualEnvironment();
    void build6RoomTest();
    int getConnections();
    void crossConnection(int connectionID);
    
    int getPlaceNow() const;
    void setPlaceNow(int);  

};

#endif
