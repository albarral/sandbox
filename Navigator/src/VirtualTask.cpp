/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualTask.h"
#include "types/TransitionType.h"

namespace sam 
{
VirtualTask::VirtualTask() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    oTask.setDatabase(oDatabase);
    stateNow = 0;
}

void VirtualTask::init(int ID)
{
    oTask.reset();
    oTask.setID(ID);
    
    loadFromMemo();
    
    if(oTask.getListStates().size() == 0)
    {
        create();
    }      
}

void VirtualTask::create()
{
    switch (oTask.getID())
    {
        case 1:
            build6RoomTest();
            break;

        case 2:
            build7RoomTest();
            break;

        case 3:
            build8RoomTest();
            break;            
    }
        
    storeInMemo();
}

void VirtualTask::storeInMemo()
{    
    oTask.storeInMemo();
}

void VirtualTask::loadFromMemo()
{    
    oTask.loadFromMemo();
}

std::vector<Transition>& VirtualTask::getPresentTransitions()
{
    State& mStateNow = oTask.getListStates().at(stateNow);
    return mStateNow.getListTransitions();
}


void VirtualTask::crossTransition(int transitionID)
{
    State& mStateNow = oTask.getListStates().at(stateNow);
    Transition& mTransition = mStateNow.getListTransitions().at(transitionID);
    setStateNow(mTransition.getNextState());
}

void VirtualTask::build6RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5;
    Transition oTransition;
    oTask.setID(1);
    
    oState0.setID(0); 
    oState0.setTaskID(1);
    oState1.setID(1); 
    oState1.setTaskID(1);
    oState2.setID(2);
    oState2.setTaskID(1);
    oState3.setID(3);    
    oState3.setTaskID(1);
    oState4.setID(4);    
    oState4.setTaskID(1);
    oState5.setID(5);
    oState5.setTaskID(1);
   
    // default connection properties for an office environment
    oTransition.setTaskID(1);
    
    // 0 -> 4
    oTransition.set(0, 4, TransitionType::eTYPE_PLANO_CORTO);
    oState0.addTransition(oTransition);

    // 1 -> 3
    oTransition.set(1, 3, TransitionType::eTYPE_SUBIDA_LARGA);
    oState1.addTransition(oTransition);   
    
    // 1 -> 5
    oTransition.set(1, 5, TransitionType::eTYPE_PLANO_CORTO);
    oState1.addTransition(oTransition);
    
    // 2 -> 3
    oTransition.set(2, 3, TransitionType::eTYPE_PLANO_CORTO);
    oState2.addTransition(oTransition);
    
    // 3 -> 1
    oTransition.set(3, 1, TransitionType::eTYPE_BAJADA_LARGA);
    oState3.addTransition(oTransition);    

    // 3 -> 2
    oTransition.set(3, 2, TransitionType::eTYPE_PLANO_CORTO);
    oState3.addTransition(oTransition);
    
    // 3 -> 4
    oTransition.set(3, 4, TransitionType::eTYPE_PLANO_LARGO);
    oState3.addTransition(oTransition);

    // 4 -> 0
    oTransition.set(4, 0, TransitionType::eTYPE_PLANO_CORTO);
    oState4.addTransition(oTransition);  
    
    // 4 -> 3
    oTransition.set(4, 3, TransitionType::eTYPE_PLANO_LARGO);
    oState4.addTransition(oTransition); 
    
    // 4 -> 5
    oTransition.set(4, 5, TransitionType::eTYPE_BAJADA_CORTA);
    oState4.addTransition(oTransition);
  
    // 5 -> 1
    oTransition.set(5, 1, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 5 -> 4    
    oTransition.set(5, 4, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    oState0.showData();
    oState1.showData();
    oState2.showData();
    oState3.showData();
    oState4.showData();
    oState5.showData();
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);  
    
    std::cout << "environment built" << std::endl << std::endl; 
}

void VirtualTask::build7RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5, oState6;
    Transition oTransition;
    oTask.setID(2);
    
    oState0.setID(0); 
    oState0.setTaskID(2);
    oState1.setID(1); 
    oState1.setTaskID(2);
    oState2.setID(2);
    oState2.setTaskID(2);
    oState3.setID(3);    
    oState3.setTaskID(2);
    oState4.setID(4);    
    oState4.setTaskID(2);
    oState5.setID(5);
    oState5.setTaskID(2);
    oState6.setID(6);
    oState6.setTaskID(2);
   
    // default connection properties for an office environment
    oTransition.setTaskID(2);
    
    // 0 -> 4
    oTransition.set(0, 4, TransitionType::eTYPE_PLANO_CORTO);
    oState0.addTransition(oTransition);

    // 1 -> 3
    oTransition.set(1, 3, TransitionType::eTYPE_SUBIDA_LARGA);
    oState1.addTransition(oTransition);   
    
    // 1 -> 5
    oTransition.set(1, 5, TransitionType::eTYPE_PLANO_CORTO);
    oState1.addTransition(oTransition);
    
    // 2 -> 3
    oTransition.set(2, 3, TransitionType::eTYPE_PLANO_CORTO);
    oState2.addTransition(oTransition);
    
    // 3 -> 1
    oTransition.set(3, 1, TransitionType::eTYPE_BAJADA_LARGA);
    oState3.addTransition(oTransition);    

    // 3 -> 2
    oTransition.set(3, 2, TransitionType::eTYPE_PLANO_CORTO);
    oState3.addTransition(oTransition);
    
    // 3 -> 4
    oTransition.set(3, 4, TransitionType::eTYPE_PLANO_LARGO);
    oState3.addTransition(oTransition);

    // 4 -> 0
    oTransition.set(4, 0, TransitionType::eTYPE_PLANO_CORTO);
    oState4.addTransition(oTransition);  
    
    // 4 -> 3
    oTransition.set(4, 3, TransitionType::eTYPE_PLANO_LARGO);
    oState4.addTransition(oTransition); 
    
    // 4 -> 6
    oTransition.set(4, 6, TransitionType::eTYPE_BAJADA_CORTA);
    oState4.addTransition(oTransition);
  
    // 5 -> 1
    oTransition.set(5, 1, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 5 -> 6    
    oTransition.set(5, 6, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    // 6 -> 4
    oTransition.set(6, 4, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 6 -> 5    
    oTransition.set(6, 5, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    oState0.showData();
    oState1.showData();
    oState2.showData();
    oState3.showData();
    oState4.showData();
    oState5.showData();
    oState6.showData();
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);
    oTask.addState(oState6);  
    
    std::cout << "environment built" << std::endl << std::endl; 
}

void VirtualTask::build8RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5, oState6, oState7;
    Transition oTransition;
    oTask.setID(3);
    
    oState0.setID(0); 
    oState0.setTaskID(3);
    oState1.setID(1); 
    oState1.setTaskID(3);
    oState2.setID(2);
    oState2.setTaskID(3);
    oState3.setID(3);    
    oState3.setTaskID(3);
    oState4.setID(4);    
    oState4.setTaskID(3);
    oState5.setID(5);
    oState5.setTaskID(3);
    oState6.setID(6);
    oState6.setTaskID(3);
    oState7.setID(7);
    oState7.setTaskID(3);
   
    // default connection properties for an office environment
    oTransition.setTaskID(3);
    
    // 0 -> 4
    oTransition.set(0, 4, TransitionType::eTYPE_PLANO_CORTO);
    oState0.addTransition(oTransition);

    // 1 -> 3
    oTransition.set(1, 3, TransitionType::eTYPE_SUBIDA_LARGA);
    oState1.addTransition(oTransition);   
    
    // 1 -> 5
    oTransition.set(1, 5, TransitionType::eTYPE_PLANO_CORTO);
    oState1.addTransition(oTransition);
    
    // 2 -> 3
    oTransition.set(2, 3, TransitionType::eTYPE_PLANO_CORTO);
    oState2.addTransition(oTransition);
    
    // 3 -> 1
    oTransition.set(3, 1, TransitionType::eTYPE_BAJADA_LARGA);
    oState3.addTransition(oTransition);    

    // 3 -> 2
    oTransition.set(3, 2, TransitionType::eTYPE_PLANO_CORTO);
    oState3.addTransition(oTransition);
    
    // 3 -> 4
    oTransition.set(3, 4, TransitionType::eTYPE_PLANO_LARGO);
    oState3.addTransition(oTransition);

    // 4 -> 0
    oTransition.set(4, 0, TransitionType::eTYPE_PLANO_CORTO);
    oState4.addTransition(oTransition);  
    
    // 4 -> 3
    oTransition.set(4, 3, TransitionType::eTYPE_PLANO_LARGO);
    oState4.addTransition(oTransition); 
    
    // 4 -> 6
    oTransition.set(4, 6, TransitionType::eTYPE_BAJADA_CORTA);
    oState4.addTransition(oTransition);
  
    // 5 -> 1
    oTransition.set(5, 1, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 5 -> 7    
    oTransition.set(5, 7, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    // 6 -> 4
    oTransition.set(6, 4, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 6 -> 7    
    oTransition.set(6, 7, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    // 7 -> 5
    oTransition.set(7, 5, TransitionType::eTYPE_PLANO_CORTO);
    oState5.addTransition(oTransition);
    
    // 7 -> 6    
    oTransition.set(7, 6, TransitionType::eTYPE_SUBIDA_CORTA);
    oState5.addTransition(oTransition);
    
    oState0.showData();
    oState1.showData();
    oState2.showData();
    oState3.showData();
    oState4.showData();
    oState5.showData();
    oState6.showData();
    oState7.showData();
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);
    oTask.addState(oState6); 
    oTask.addState(oState7); 
    
    std::cout << "environment built" << std::endl << std::endl; 
}

}