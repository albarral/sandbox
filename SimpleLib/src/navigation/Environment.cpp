/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Environment.h"

using namespace std;

namespace sam
{
Environment::Environment()
{
    ID = -1;
}

void Environment::addPlace(Place& oPlace)
{
    listPlaces.push_back(oPlace);
}

void Environment::resetPlaces()
{
    listPlaces.clear();
}

}