
/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include <iostream>
#include <string>
#ifndef __TRANSITION_H
#define __TRANSITION_H

#include "opencv2/core/core.hpp"

using namespace std;

class Transition
{
private:
    int ID;
    string desc;
    int taskID;
    int stateID;
    int nextState;
    float cost;
    float q;
  
public:
    Transition();
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getTaskID() const;
    void setTaskID(int);
    
    int getStateID() const;
    void setStateID(int);
    
    int getNextState() const;
    void setNextState(int);
    
    float getCost() const;
    void setCost(float);
    
    float getQ() const;
    void setQ(float);

};

#endif
