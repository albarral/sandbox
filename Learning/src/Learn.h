#ifndef __SAM_LEARN_H
#define __SAM_LEARN_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "Connection.h"
#include "Place.h"

#include "sam/utils/Database.h"

namespace sam
{
class Learn
{
private:   
    float gamma;
    
public:
    Learn();
    
    float getGamma() {return gamma;};
    void setGamma(float Gamma) {gamma = Gamma;};

    float computeQ(Connection oConn, Place oPlace);
    float maxQvalue(Place oPlace);
};

}

#endif
