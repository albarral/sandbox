#ifndef __VITUALTASK_H
#define __VIRTUALTASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Task.h"
#include "Transition.h"
#include "sam/utils/Database.h"

namespace sam 
{
class VirtualTask
{
private:
    Task oTask;
    Database oDatabase;
    int stateNow;
    
public:
    VirtualTask();
    
    void init(int ID);

    int getStateNow() {return stateNow;};
    void setStateNow(int sNow) {stateNow = sNow;};  
    std::vector<Transition>& getPresentTransitions();    
    void crossTransition(int transitionID);
    
private:
    void create();
    void storeInMemo();
    void loadFromMemo();

    void build6RoomTest();
    void build7RoomTest();
    void build8RoomTest(); 

};
}

#endif
