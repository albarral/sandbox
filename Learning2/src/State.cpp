/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "State.h"

namespace sam 
{
State::State() 
{
    ID = 0;
    taskID = 0;
    reward = 0; // 0.0 or 0f
}

void State::addTransition(Transition& oTransition)
{
    // transition ID is assigned automatically
    oTransition.setID(listTransitions.size());
    listTransitions.push_back(oTransition);
}

void State::loadFromMemo()
{}

int State::getID() const
{ 
    return ID; 
}

void State::setID(int id)
{
    ID = id;
}    

std::string State::getDesc() const
{ 
    return desc; 
}

void State::setDesc(std::string de)
{
    desc = de;
}

int State::getTaskID() const
{ 
    return taskID; 
}

void State::setTaskID(int tID)
{
    taskID = tID;
}   

float State::getReward() const
{ 
    return taskID; 
}

void State::setReward(float rwrd)
{
    reward = rwrd;
} 

std::vector<Transition> State::getListTransitions() const
{
    return listTransitions;
}

}