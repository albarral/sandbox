/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualTask.h"

namespace sam 
{
VirtualTask::VirtualTask() 
{
    stateNow = 0;
}

void VirtualTask::build6RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5;
    Transition oTransition;
    oTask.setID(1);
    
    oState0.setID(0);    
    oState1.setID(1);    
    oState2.setID(2);
    oState3.setID(3);    
    oState4.setID(4);    
    oState5.setID(5);
   
    oTransition.setID(1);
    oTransition.setStateID(0);
    oTransition.setNextState(4);
    oState0.addTransition(oTransition);
    
    oTransition.setID(2);
    oTransition.setStateID(1);
    oTransition.setNextState(3);
    oState1.addTransition(oTransition);
    
    oTransition.setID(3);
    oTransition.setNextState(5);
    oState1.addTransition(oTransition);
    
    oTransition.setID(4);
    oTransition.setStateID(2);
    oTransition.setNextState(3);
    oState2.addTransition(oTransition);
    
    oTransition.setID(5);
    oTransition.setStateID(3);
    oTransition.setNextState(1);
    oState3.addTransition(oTransition);
    
    oTransition.setID(6);
    oTransition.setNextState(2);
    oState3.addTransition(oTransition);
    
    oTransition.setID(7);
    oTransition.setNextState(4);
    oState3.addTransition(oTransition);
    
    oTransition.setID(8);
    oTransition.setStateID(4);
    oTransition.setNextState(0);
    oState4.addTransition(oTransition);
    
    oTransition.setID(9);
    oTransition.setNextState(3);
    oState4.addTransition(oTransition);
    
    oTransition.setID(10);
    oTransition.setNextState(5);
    oState4.addTransition(oTransition);
    
    oTransition.setID(11);
    oTransition.setStateID(5);
    oTransition.setNextState(1);
    oState5.addTransition(oTransition);
    
    oTransition.setID(12);
    oTransition.setNextState(4);
    oState5.addTransition(oTransition);
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);
       
}

int VirtualTask::getTransitions()
{
    int transitionID;
    int statenow = getStateNow();
    std::vector<int> listTransitionsIDs;
    
    // prepare the list iterator
    State& mStateNow = oTask.getListStates().at(statenow);
    std::vector<Transition>::iterator it_transitions = mStateNow.getListTransitions().begin();
    std::vector<Transition>::iterator it_end = mStateNow.getListTransitions().end();
    // walk the list getting the connection IDs
    while (it_transitions != it_end)
    {
        transitionID = it_transitions->getID();
        std::cout<< "Transition: " <<transitionID<<std::endl;
        listTransitionsIDs.push_back(transitionID);
        it_transitions++;	
    }
    
    return transitionID; //Devuelve la última ID de Transition, no el State al que ha de ir
}

void VirtualTask::crossTransition(int transitionID) // de la transitionID tengo que coger el nextPlace
{
    int statenow = getStateNow();  
    State& mStateNow = oTask.getListStates().at(statenow);
    Transition& mTranID = mStateNow.getListTransitions().at(transitionID); //Peta esta línea
    int nxtStt = mTranID.getNextState();
    stateNow = nxtStt;
}

int VirtualTask::getStateNow() const
{ 
    return stateNow; 
}

void VirtualTask::setStateNow(int pNow)
{
    stateNow = pNow;
}   

}