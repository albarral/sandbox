/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include "Task.h"

Task::Task() 
{
    ID = 0;
    type= 0;
}

void Task::addState(State& oState)
{
    listStates.push_back(oState);
}

void Task::loadFromMemo()
{}

int Task::getID() const
{ 
    return ID; 
}

void Task::setID(int id)
{
    ID = id;
}    

string Task::getDesc() const
{ 
    return desc; 
}

void Task::setDesc(string de)
{
    desc = de;
}

int Task::getType() const
{ 
    return type; 
}

void Task::setType(int ty)
{
    type = ty;
}   

vector<State> Task::getListStates() const
{
    return listStates;
}

void Task::setListStates(vector<State> states)
{
    listStates = states;
}