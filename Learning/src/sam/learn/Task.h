#ifndef __SAM_LEARN_TASK_H
#define __SAM_LEARN_TASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/learn/State.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace learn
{
class Task
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<State> listStates;
    utilsDB::Database* pDatabase;
    
public:
    Task();
    
    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getType() {return type;};
    void setType(int value) {type = value;};
    
    std::vector<State>& getListStates() {return listStates;}; 
    void addState(State& oState);
    
    void setDatabase(utilsDB::Database& oDatabase) {pDatabase = &oDatabase;}
    
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();
    void storeQ();
    void reset();
    
    std::string showData();

private:
    void statesFromMemo(sql::Connection* con);
    void loadStates(sql::Connection* con);
    void storeStates(sql::Connection* con);


};
}
}

#endif
