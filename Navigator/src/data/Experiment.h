#ifndef __SAM_NAV_EXPERIMENT_H
#define __SAM_NAV_EXPERIMENT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "modules/Navigation.h"

namespace sam
{
class Experiment
{
private:   
    int firstPlace;
    int targetPlace;
    int maxSteps;   // max steps allowed in the navigation experiment
    bool bexploration;
    
public:
    Experiment();
   
    // sets the experiment parameters
    void setParams(int firstPlace, int targetPlace, int maxSteps, bool bexploration);
    
    int getFirstPlace() {return firstPlace;};
    int getTargetPlace() {return targetPlace;};
    int getMaxSteps() {return maxSteps;};
    bool getExplorationMode() {return bexploration;};
    
};

}

#endif
