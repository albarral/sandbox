#ifndef __SAM_LEARN_LEARNNAV_H
#define __SAM_LEARN_LEARNNAV_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "Connection.h"
#include "Place.h"

namespace sam
{
class LearnNav
{
private:   
    float gamma;
    
public:
    LearnNav();
    
    float getGamma() {return gamma;};
    void setGamma(float value) {gamma = value;};

    // Compute the Q value from a state with one connection
    float computeQ(Place& oPlace);
   
private:    
    float maxQvalue(Place& oPlace);
};

}

#endif
