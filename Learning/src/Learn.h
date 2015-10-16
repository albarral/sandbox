#ifndef __SAM_LEARN_H
#define __SAM_LEARN_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "State.h"

namespace sam
{
class Learn
{
private:   
    float gamma;
    static log4cxx::LoggerPtr logger;
    
public:
    Learn();
    
    float getGamma() {return gamma;};
    void setGamma(float value) {gamma = value;};

    // Compute the Q value from a state with one connection
    float computeQ(State& oState);
   
private:    
    float maxQValue(State& oState);
};

}

#endif
