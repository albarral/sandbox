#ifndef __SAM_TASK_H
#define __SAM_TASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "State.h"
#include "sam/utils/Database.h"

namespace sam 
{
class Task
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<State> listStates;
    Database* pDatabase;
    
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
    
    void setDatabase(Database& oDatabase) {pDatabase = &oDatabase;}
    
    void loadFromMemo();
    void storeInMemo();
    void upDateInMemo();
    void deleteFromMemo();
    void reset();
    
    std::string showData();

private:
    void statesFromMemo(sql::Connection *con);
    void loadStates(sql::Connection *con);
    void storeStates(sql::Connection *con);


};
}

#endif
