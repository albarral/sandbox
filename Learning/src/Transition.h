#ifndef __TRANSITION_H
#define __TRANSITION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>


namespace sam 
{
class Transition
{
private:
    int ID;
    std::string desc;
    int taskID;
    int stateID;
    int nextState;
    float cost;
    float Q;
  
public:
    Transition();
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    std::string getDesc() const;
    void setDesc(std::string);
    
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
}

#endif
