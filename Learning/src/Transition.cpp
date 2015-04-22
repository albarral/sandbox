/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include "Transition.h"

Transition::Transition() 
{
    ID = 0;
    taskID = 0;
    stateID = 0;
    nextState = 0;
    cost = 0; // 0.0 or 0f
    q = 0; // 0.0 or 0f
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

string Transition::getDesc() const
{ 
    return desc; 
}

void Transition::setDesc(string de)
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
    return q; 
}

void Transition::setQ(float Q)
{
    q = Q;
} 