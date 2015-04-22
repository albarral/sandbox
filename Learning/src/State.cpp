/* 
 * 
 * Author: Ainoa Millán
 *
 */


#include "State.h"

State::State() 
{
    ID = 0;
    taskID = 0;
    reward = 0; // 0.0 or 0f
}

void State::addTransition(Transition& oTransition)
{
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

string State::getDesc() const
{ 
    return desc; 
}

void State::setDesc(string de)
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

vector<Transition> State::getListTransitions() const
{
    return listTransitions;
}

void State::setListTransitions(vector<Transition> transitions)
{
    listTransitions = transitions;
}