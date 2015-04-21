/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Place.h"

namespace sam
{
Place::Place()
{
    ID = -1;
}

void Place::addConnection(Connection& oConnection)
{
    listConnections.push_back(oConnection);
}

void Place::resetConnections()
{
    listConnections.clear();
}
}