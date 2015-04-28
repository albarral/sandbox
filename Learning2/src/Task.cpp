/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Task.h"

namespace sam 
{
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

std::string Task::getDesc() const
{ 
    return desc; 
}

void Task::setDesc(std::string de)
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

std::vector<State> Task::getListStates() const
{
    return listStates;
}

}