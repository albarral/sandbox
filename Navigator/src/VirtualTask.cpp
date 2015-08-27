/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualTask.h"
#include "types/TransitionType.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr VirtualTask::logger(Logger::getLogger("sam.navigation"));
    
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
    
    if (oTask.getListStates().size() == 0)
    {
        create();
    } 
    
    describeTask(&oTask);
}

void VirtualTask::create()
{
    switch (oTask.getID())
    {
        case eENV_6ROOM:
            build6RoomTest();
            break;

        case eENV_7ROOM:
            build7RoomTest();
            break;

        case eENV_8ROOM:
            build8RoomTest();
            break;   
            
        default:
            // invalid value
            return;
    }
        
    storeInMemo();
}

void VirtualTask::storeInMemo()
{    
    oTask.storeInMemo();
}

void VirtualTask::loadFromMemo()
{   
    LOG4CXX_INFO(logger, "Loading task from DB ..."); 
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

void VirtualTask::describeTask(Task* pTask)
{
    // describe the task
    LOG4CXX_INFO(logger, pTask->showData());
    
    // describe its states
    std::vector<State>::iterator it_state = pTask->getListStates().begin();
    std::vector<State>::iterator it_end = pTask->getListStates().end();
    while (it_state != it_end)
    {
        describeState(&(*it_state));
        it_state++;
    } 
}

void VirtualTask::describeState(State* pState)
{
    // describe the state
    LOG4CXX_INFO(logger, pState->showData());

    // describe its connections
    std::vector<Transition>::iterator it_trans = pState->getListTransitions().begin();
    std::vector<Transition>::iterator it_end = pState->getListTransitions().end();
    while (it_trans != it_end)
    {
        LOG4CXX_INFO(logger, it_trans->showData());
        it_trans++;
    }
}

void VirtualTask::build6RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5;
    Transition oTransition;
    int taskID = oTask.getID();
    
    LOG4CXX_INFO(logger, "Building 6 room environment ... taskID=" << taskID);  
    
    oTask.setDesc("6 room");
    oState0.setID(0); 
    oState0.setTaskID(taskID);
    oState1.setID(1); 
    oState1.setTaskID(taskID);
    oState2.setID(2);
    oState2.setTaskID(taskID);
    oState3.setID(3);    
    oState3.setTaskID(taskID);
    oState4.setID(4);    
    oState4.setTaskID(taskID);
    oState5.setID(5);
    oState5.setTaskID(taskID);
   
    // default connection properties for an office environment
    oTransition.setTaskID(taskID);
    
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
    
    LOG4CXX_INFO(logger, oState0.showData());
    LOG4CXX_INFO(logger, oState1.showData());
    LOG4CXX_INFO(logger, oState2.showData());
    LOG4CXX_INFO(logger, oState3.showData());
    LOG4CXX_INFO(logger, oState4.showData());
    LOG4CXX_INFO(logger, oState5.showData());
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);  
    
    LOG4CXX_INFO(logger, "task built");  
}

void VirtualTask::build7RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5, oState6;
    Transition oTransition;
    int taskID = oTask.getID();
    
    LOG4CXX_INFO(logger, "Building 7 room environment ... taskID=" << taskID);  
    
    oTask.setDesc("7 room");   
    oState0.setID(0); 
    oState0.setTaskID(taskID);
    oState1.setID(1); 
    oState1.setTaskID(taskID);
    oState2.setID(2);
    oState2.setTaskID(taskID);
    oState3.setID(3);    
    oState3.setTaskID(taskID);
    oState4.setID(4);    
    oState4.setTaskID(taskID);
    oState5.setID(5);
    oState5.setTaskID(taskID);
    oState6.setID(6);
    oState6.setTaskID(taskID);
   
    // default connection properties for an office environment
    oTransition.setTaskID(taskID);
    
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
    
    LOG4CXX_INFO(logger, oState0.showData());
    LOG4CXX_INFO(logger, oState1.showData());
    LOG4CXX_INFO(logger, oState2.showData());
    LOG4CXX_INFO(logger, oState3.showData());
    LOG4CXX_INFO(logger, oState4.showData());
    LOG4CXX_INFO(logger, oState5.showData());
    LOG4CXX_INFO(logger, oState6.showData());
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);
    oTask.addState(oState6);  
    
    LOG4CXX_INFO(logger, "task built"); 
}

void VirtualTask::build8RoomTest()
{
    State oState0, oState1, oState2, oState3, oState4, oState5, oState6, oState7;
    Transition oTransition;
    int taskID = oTask.getID();
    
    LOG4CXX_INFO(logger, "Building 8 room environment ... taskID=" << taskID);  
    
    oTask.setDesc("8 room");    
    oState0.setID(0); 
    oState0.setTaskID(taskID);
    oState1.setID(1); 
    oState1.setTaskID(taskID);
    oState2.setID(2);
    oState2.setTaskID(taskID);
    oState3.setID(3);    
    oState3.setTaskID(taskID);
    oState4.setID(4);    
    oState4.setTaskID(taskID);
    oState5.setID(5);
    oState5.setTaskID(taskID);
    oState6.setID(6);
    oState6.setTaskID(taskID);
    oState7.setID(7);
    oState7.setTaskID(taskID);
   
    // default connection properties for an office environment
    oTransition.setTaskID(taskID);
    
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
    
    LOG4CXX_INFO(logger, oState0.showData());
    LOG4CXX_INFO(logger, oState1.showData());
    LOG4CXX_INFO(logger, oState2.showData());
    LOG4CXX_INFO(logger, oState3.showData());
    LOG4CXX_INFO(logger, oState4.showData());
    LOG4CXX_INFO(logger, oState5.showData());
    LOG4CXX_INFO(logger, oState6.showData());
    LOG4CXX_INFO(logger, oState7.showData());
    
    oTask.addState(oState0);
    oTask.addState(oState1);
    oTask.addState(oState2);
    oTask.addState(oState3);
    oTask.addState(oState4);
    oTask.addState(oState5);
    oTask.addState(oState6); 
    oTask.addState(oState7); 
    
    LOG4CXX_INFO(logger, "task built"); 
}

}