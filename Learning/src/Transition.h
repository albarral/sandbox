#ifndef __SAM_TRANSITION_H
#define __SAM_TRANSITION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/utils/Database.h"

namespace sam 
{
class Transition
{
private:
    int ID;
    std::string desc;
    int taskID;
    int stateID;
    int nextState;
    float cost;
    float Q;
  
public:
    Transition();
    
    void loadFromMemo(Database* pDatabase, sql::Connection *con);
    void storeInMemo(Database* pDatabase, sql::Connection *con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    
    // sets 6 members at a time (type is a TransitionType predefined type)
    void set(int stateID, int nextState, int type);
    
    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getTaskID() {return taskID;};
    void setTaskID(int value) {taskID = value;};
    
    int getStateID() {return stateID;};
    void setStateID(int value) {stateID = value;};
    
    int getNextState() {return nextState;};
    void setNextState(int value) {nextState = value;};
    
    float getCost() {return cost;};
    void setCost(float value) {cost = value;};
    
    float getQ() {return Q;};
    void setQ(float value) {Q = value;};
    
    float computeCost();
    
    std::string showData();
};
}

#endif
