#ifndef __VITUALTASK_H
#define __VIRTUALTASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Task.h"
#include "Transition.h"

namespace sam 
{
class VirtualTask
{
private:
    Task oTask;
    int stateNow;
    
public:
    VirtualTask();
    void build6RoomTest();
    int getTransitions();
    void crossTransition(int transitionID);
    
    int getStateNow() const;
    void setStateNow(int);  

};
}

#endif
