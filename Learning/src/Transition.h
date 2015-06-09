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
    void setID(int id) {ID = id;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string de) {desc = de;};
    
    int getTaskID() {return taskID;};
    void setTaskID(int tID) {taskID = tID;};
    
    int getStateID() {return stateID;};
    void setStateID(int sID) {stateID = sID;};
    
    int getNextState() {return nextState;};
    void setNextState(int nStt) {nextState = nStt;};
    
    float getCost() {return cost;};
    void setCost(float cst) {cost = cst;};
    
    float getQ() {return Q;};
    void setQ(float q) {Q = q;};
    
    float computeCost();
    
    std::string showData();
};
}

#endif
