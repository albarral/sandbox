#ifndef __VITUALTASK_H
#define __VIRTUALTASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "Task.h"
#include "Transition.h"
#include "sam/utils/Database.h"

namespace sam 
{
class VirtualTask
{
    
public:
    // environments
    enum eType
    {
        eENV_6ROOM, 
        eENV_7ROOM, 
        eENV_8ROOM, 
        eENV_UNKNOWN, 
    };
    
private:
    static log4cxx::LoggerPtr logger;
    Task oTask;
    Database oDatabase;
    int stateNow;
    
public:
    VirtualTask();
    
    void init(int ID);

    int getStateNow() {return stateNow;};
    void setStateNow(int value) {stateNow = value;}; 
    
    std::vector<Transition>& getPresentTransitions();    
    void crossTransition(int transitionID);
    
private:
    void create();
    void storeInMemo();
    void loadFromMemo();
    
    // shows brief description of given task
    void describeTask(Task* pTask);
    // shows brief description of given state
    void describeState(State* pState);

    void build6RoomTest();
    void build7RoomTest();
    void build8RoomTest(); 

};
}

#endif
