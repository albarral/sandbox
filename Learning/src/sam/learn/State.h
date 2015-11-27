#ifndef __SAM_LEARN_STATE_H
#define __SAM_LEARN_STATE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/learn/Transition.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace learn
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
    void loadFromMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void storeInMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void upDateInMemo(utilsDB::Database* pDatabase);
    void deleteFromMemo(utilsDB::Database* pDatabase);
    void storeQ(utilsDB::Database* pDatabase, sql::Connection* con);
    
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
    void transitionsFromMemo(utilsDB::Database* pDatabase, sql::Connection* con);
    void loadTransitions(utilsDB::Database* pDatabase, sql::Connection* con);
    void storeTransitions(utilsDB::Database* pDatabase, sql::Connection* con);
};
}
}

#endif
