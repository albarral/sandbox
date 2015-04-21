#ifndef __PLACE_H
#define __PLACE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include <vector>
#include "navigation/Connection.h"

namespace sam 
{
// Class to represent places in a environment
class Place
{
private:
    int ID;
    std::vector<Connection> listConnections;

public:

    Place();

    int getID() {return ID;};
    void setID(int ID) {this->ID = ID;};

    void addConnection(Connection& oConnection);
    std::vector<Connection> getListConnections() {return listConnections;};;
    void resetConnections();    
    
};
}

#endif
