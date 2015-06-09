#ifndef __SAM_STATE_H
#define __SAM_STATE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Transition.h"
#include "sam/utils/Database.h"

namespace sam 
{
class State
{
private:
    int ID;
    std::string desc;
    int taskID;
    float reward;
    std::vector<Transition> listTransitions;
    
public:
    State();
    void addTransition(Transition& oTransition);
    void loadFromMemo(Database* pDatabase, sql::Connection *con);
    void storeInMemo(Database* pDatabase, sql::Connection *con);
    void upDateInMemo(Database* pDatabase);
    void deleteFromMemo(Database* pDatabase);
    
    int getID() {return ID;};
    void setID(int id) {ID = id;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string de) {desc = de;};
    
    int getTaskID() {return taskID;};
    void setTaskID(int tID) {taskID = tID;};
    
    float getReward() {return reward;};
    void setReward(float rwrd) {reward = rwrd;};
  
    std::vector<Transition>& getListTransitions() {return listTransitions;};

    std::string showData();
   
private:
    void transitionsFromMemo(Database* pDatabase, sql::Connection *con);
    void loadTransitions(Database* pDatabase, sql::Connection *con);
    void storeTransitions(Database* pDatabase, sql::Connection *con);
};
}

#endif
