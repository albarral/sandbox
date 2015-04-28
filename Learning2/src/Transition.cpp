/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Transition.h"

namespace sam 
{
Transition::Transition() 
{
    ID = 0;
    taskID = 0;
    stateID = 0;
    nextState = 0;
    cost = 0; // 0.0 or 0f
    Q = 0; // 0.0 or 0f
}

void Transition::loadFromMemo()
{}

int Transition::getID() const
{ 
    return ID; 
}

void Transition::setID(int id)
{
    ID = id;
}    

std::string Transition::getDesc() const
{ 
    return desc; 
}

void Transition::setDesc(std::string de)
{
    desc = de;
}

int Transition::getTaskID() const
{ 
    return taskID; 
}

void Transition::setTaskID(int tID)
{
    taskID = tID;
}  

int Transition::getStateID() const
{ 
    return stateID; 
}

void Transition::setStateID(int sID)
{
    stateID = sID;
} 

int Transition::getNextState() const
{ 
    return nextState; 
}

void Transition::setNextState(int nStt)
{
    nextState = nStt;
}

float Transition::getCost() const
{ 
    return cost; 
}

void Transition::setCost(float cst)
{
    cost = cst;
} 

float Transition::getQ() const
{ 
    return Q; 
}

void Transition::setQ(float q)
{
    Q = q;
} 

}