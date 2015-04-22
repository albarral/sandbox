#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include "navigation/Place.h"

namespace sam 
{
// Class to represent a environment as a list of places linked by connections
class Environment
{
private:
    int ID;
    std::vector<Place> listPlaces;

public:

    Environment();

    int getID() {return ID;};
    void setID(int ID) {this->ID = ID;};

    void addPlace(Place& oPlace);
    std::vector<Place> getListPlaces() {return listPlaces;};;
    void resetPlaces();    
    
};
}

#endif
