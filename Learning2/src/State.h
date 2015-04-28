#ifndef __STATE_H
#define __STATE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "Transition.h"

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
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
    int getTaskID() const;
    void setTaskID(int);
    
    float getReward() const;
    void setReward(float);
    
    std::vector<Transition> getListTransitions() const;

};
}

#endif
