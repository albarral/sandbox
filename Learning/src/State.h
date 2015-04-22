
/* 
 * 
 * Author: Ainoa Millán
 *
 */


#include <iostream>
#include <string>
#ifndef __STATE_H
#define __STATE_H

#include "Transition.h"
#include "opencv2/core/core.hpp"

using namespace std;

class State
{
private:
    int ID;
    string desc;
    int taskID;
    float reward;
    vector<Transition> listTransitions;
    
public:
    State();
    void addTransition(Transition& oTransition);
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getTaskID() const;
    void setTaskID(int);
    
    float getReward() const;
    void setReward(float);
    
    vector<Transition> getListTransitions() const;
    void setListTransitions(vector<Transition>);

   
};

#endif
