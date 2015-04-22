/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include <iostream>
#include <string>
#ifndef __TASK_H
#define __TASK_H

#include "State.h"
#include "opencv2/core/core.hpp"

using namespace std;

class Task
{
private:
    int ID;
    string desc;
    int type;
    vector<State> listStates;
    
public:
    Task();
    void addState(State& oState);
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getType() const;
    void setType(int);
    
    vector<State> getListStates() const;
    void setListStates(vector<State>);

   
};

#endif
