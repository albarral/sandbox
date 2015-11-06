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
protected:
    int ID;
    std::string desc;
    int taskID;
    float reward;
    std::vector<Transition> listTransitions;
    
public:
    State();
    void addTransition(Transition& oTransition);
    void loadFromMemo(utils::Database* pDatabase, sql::Connection* con);
    void storeInMemo(utils::Database* pDatabase, sql::Connection* con);
    void upDateInMemo(utils::Database* pDatabase);
    void deleteFromMemo(utils::Database* pDatabase);
    void storeQ(utils::Database* pDatabase, sql::Connection* con);
    
    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getTaskID() {return taskID;};
    void setTaskID(int value) {taskID = value;};
    
    float getReward() {return reward;};
    void setReward(float value) {reward = value;};
      
    std::vector<Transition>& getListTransitions() {return listTransitions;};

    std::string showData();
   
//private:
    void transitionsFromMemo(utils::Database* pDatabase, sql::Connection* con);
    void loadTransitions(utils::Database* pDatabase, sql::Connection* con);
    void storeTransitions(utils::Database* pDatabase, sql::Connection* con);
};
}

#endif
