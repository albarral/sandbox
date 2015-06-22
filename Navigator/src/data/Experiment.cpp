/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Experiment.h"

namespace sam
{   
Experiment::Experiment()
{
    firstPlace = 0;
    targetPlace = 0;
    maxSteps = 0;
    bexploration = false;
}

void Experiment::setParams(int firstPlace, int targetPlace, int maxSteps, bool bexploration)
{
    this->firstPlace = firstPlace;
    this->targetPlace = targetPlace;
    this->maxSteps = maxSteps;
    this->bexploration = bexploration;    
}
}