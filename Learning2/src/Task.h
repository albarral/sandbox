#ifndef __TASK_H
#define __TASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "State.h"

namespace sam 
{
class Task
{
private:
    int ID;
    std::string desc;
    int type;
    std::vector<State> listStates;
    
public:
    Task();
    void addState(State& oState);
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
    int getType() const;
    void setType(int);
    
    std::vector<State> getListStates() const;
};
}

#endif
