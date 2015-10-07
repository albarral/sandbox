/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "GameTask.h"

namespace sam 
{
log4cxx::LoggerPtr GameTask::logger(log4cxx::Logger::getLogger("sam.player"));
GameTask::GameTask() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    setDatabase(oDatabase);
}

void GameTask::init(int ID)
{
    reset();
    setID(ID);

    //loadFromMemo();
    
    //if (getListStates().size() == 0) // || getListGameStates().size == 0)
    //{
        create();
    //} 

    describeTask();   
}

void GameTask::addGameState(GameState& oGameState)
{
    listGameStates.push_back(oGameState);
}

void GameTask::create()
{
    switch (getID())
    {
        case eTASK_TICTACTOE:
            buildTicTacToe();
            break;
            
        default:
            // invalid value
            return;
    }
    storeInMemo();
}

void GameTask::describeTask()
{
    // describe the task
    LOG4CXX_INFO(logger, showData());
    
    // describe its states
    std::vector<GameState>::iterator it_state = getListGameStates().begin();
    std::vector<GameState>::iterator it_end = getListGameStates().end();
    while (it_state != it_end)
    {
        describeState(&(*it_state));
        it_state++;
    } 
}

void GameTask::describeState(GameState* pGameState)
{
    // describe the state
    LOG4CXX_INFO(logger, pGameState->showData());

    // describe its connections
    std::vector<Transition>::iterator it_trans = pGameState->getListTransitions().begin();
    std::vector<Transition>::iterator it_end = pGameState->getListTransitions().end();
    while (it_trans != it_end)
    {
        LOG4CXX_INFO(logger, it_trans->showData());
        it_trans++;
    }
}
    
void GameTask::buildTicTacToe()
{
    GameState oGameState0, oGameState1, oGameState2, oGameState3, oGameState4, oGameState5, oGameState6, 
            oGameState7, oGameState8, oGameState9, oGameState10, oGameState11, oGameState12, oGameState13,
            oGameState14, oGameState15, oGameState16, oGameState17, oGameState18, oGameState19, oGameState20, 
            oGameState21, oGameState22, oGameState23, oGameState24, oGameState25, oGameState26;
    Transition oTransition;
    int taskID = getID();
    
    LOG4CXX_INFO(logger, "Building tic tac toe ... taskID=" << taskID); 
    
    setDesc("Tic Tac Toe");

    // set ( pos1, pos2, pos3, numMines, numOthers )
    oGameState0.setID(0); 
    oGameState0.setTaskID(taskID);
    oGameState0.set(0, 0, 0, 0, 0); 
    oGameState1.setID(1); 
    oGameState1.setTaskID(taskID);
    oGameState1.set(0, 0, 1, 1, 0);
    oGameState2.setID(2); 
    oGameState2.setTaskID(taskID);
    oGameState2.set(0, 0, 2, 0, 1);
    oGameState3.setID(3); 
    oGameState3.setTaskID(taskID);
    oGameState3.set(0, 1, 0, 1, 0);
    oGameState4.setID(4); 
    oGameState4.setTaskID(taskID);    
    oGameState4.set(0, 1, 1, 2, 0);
    oGameState5.setID(5); 
    oGameState5.setTaskID(taskID);
    oGameState5.set(0, 1, 2, 1, 1);
    oGameState6.setID(6); 
    oGameState6.setTaskID(taskID);
    oGameState6.set(0, 2, 0, 0, 1);
    oGameState7.setID(7); 
    oGameState7.setTaskID(taskID);
    oGameState7.set(0, 2, 1, 1, 1);
    oGameState8.setID(8); 
    oGameState8.setTaskID(taskID);
    oGameState8.set(0, 2, 2, 0, 2);
    oGameState9.setID(9); 
    oGameState9.setTaskID(taskID);
    oGameState9.set(1, 0, 0, 1, 0);
    oGameState10.setID(10); 
    oGameState10.setTaskID(taskID);
    oGameState10.set(1, 0, 1, 2, 0);
    oGameState11.setID(11); 
    oGameState11.setTaskID(taskID);
    oGameState11.set(1, 0, 2, 1, 1);
    oGameState12.setID(12); 
    oGameState12.setTaskID(taskID);
    oGameState12.set(1, 1, 0, 2, 0);
    oGameState13.setID(13); 
    oGameState13.setTaskID(taskID);
    oGameState13.set(1, 1, 1, 3, 0);
    oGameState14.setID(14); 
    oGameState14.setTaskID(taskID);
    oGameState14.set(1, 1, 2, 2, 1);
    oGameState15.setID(15); 
    oGameState15.setTaskID(taskID);
    oGameState15.set(1, 2, 0, 1, 1);
    oGameState16.setID(16); 
    oGameState16.setTaskID(taskID);    
    oGameState16.set(1, 2, 1, 2, 1);
    oGameState17.setID(17); 
    oGameState17.setTaskID(taskID);
    oGameState17.set(1, 2, 2, 1, 2);
    oGameState18.setID(18); 
    oGameState18.setTaskID(taskID);
    oGameState18.set(2, 0, 0, 0, 1);
    oGameState19.setID(19); 
    oGameState19.setTaskID(taskID);
    oGameState19.set(2, 0, 1, 1, 1);
    oGameState20.setID(20); 
    oGameState20.setTaskID(taskID);
    oGameState20.set(2, 0, 2, 0, 2);
    oGameState21.setID(21); 
    oGameState21.setTaskID(taskID);
    oGameState21.set(2, 1, 0, 1, 1);
    oGameState22.setID(22); 
    oGameState22.setTaskID(taskID);    
    oGameState22.set(2, 1, 1, 2, 1);
    oGameState23.setID(23); 
    oGameState23.setTaskID(taskID);
    oGameState23.set(2, 1, 2, 1, 2);
    oGameState24.setID(24); 
    oGameState24.setTaskID(taskID);
    oGameState24.set(2, 2, 0, 0, 2);
    oGameState25.setID(25); 
    oGameState25.setTaskID(taskID);
    oGameState25.set(2, 2, 1, 1, 2);
    oGameState26.setID(26); 
    oGameState26.setTaskID(taskID);
    oGameState26.set(2, 2, 2, 0, 3);

    // default connection properties for an office environment
    oTransition.setTaskID(taskID);
    
    // (0, 0, 0) to (0, 0, 1)   ->  0 to 1
    oTransition.set(0, 1);
    oGameState0.addTransition(oTransition);
    
    // (0, 0, 0) to (0, 1, 0)   ->  0 to 3
    oTransition.set(0, 3);
    oGameState0.addTransition(oTransition);
    
    // (0, 0, 0) to (1, 0, 0)   ->  0 to 9
    oTransition.set(0, 9);
    oGameState0.addTransition(oTransition);
    
    // (0, 0, 1) to (0, 1, 1)   ->  1 to 4
    oTransition.set(1, 4);
    oGameState1.addTransition(oTransition);
    
    // (0, 0, 1) to (1, 0, 1)   ->  1 to 10
    oTransition.set(1, 10);
    oGameState1.addTransition(oTransition);
    
    // (0, 0, 2) to (0, 1, 2)   ->  2 to 5
    oTransition.set(2, 5);
    oGameState2.addTransition(oTransition);
    
    // (0, 0, 2) to (1, 0, 2)   ->  2 to 11
    oTransition.set(2, 11);
    oGameState2.addTransition(oTransition);
    
    // (0, 1, 0) to (0, 1, 1)   ->  3 to 4
    oTransition.set(3, 4);
    oGameState3.addTransition(oTransition);
    
    // (0, 1, 0) to (1, 1, 0)   ->  3 to 12
    oTransition.set(3, 12);
    oGameState3.addTransition(oTransition);
    
    // (0, 1, 1) to (1, 1, 1)   ->  4 to 13
    oTransition.set(4, 13);
    oGameState4.addTransition(oTransition);
    
    // (0, 1, 2) to (1, 1, 2)   ->  5 to 14
    oTransition.set(5, 14);
    oGameState5.addTransition(oTransition);
    
    // (0, 2, 0) to (0, 2, 1)   ->  6 to 7
    oTransition.set(6, 7);
    oGameState6.addTransition(oTransition);
    
    // (0, 2, 0) to (1, 2, 0)   ->  6 to 15
    oTransition.set(6, 15);
    oGameState6.addTransition(oTransition);
    
    // (0, 2, 1) to (1, 2, 1)   ->  7 to 16
    oTransition.set(7, 16);
    oGameState7.addTransition(oTransition);
    
    // (0, 2, 2) to (1, 2, 2)   ->  8 to 17
    oTransition.set(8, 17);
    oGameState8.addTransition(oTransition);
    
    // (1, 0, 0) to (1, 0, 1)   ->  9 to 10
    oTransition.set(9, 10);
    oGameState9.addTransition(oTransition);
    
    // (1, 0, 0) to (1, 1, 0)   ->  9 to 12
    oTransition.set(9, 12);
    oGameState9.addTransition(oTransition);
    
    // (1, 0, 1) to (1, 1, 1)   ->  10 to 13
    oTransition.set(10, 13);
    oGameState10.addTransition(oTransition);
    
    // (1, 0, 2) to (1, 1, 2)   ->  11 to 14
    oTransition.set(11, 14);
    oGameState11.addTransition(oTransition);
    
    // (1, 1, 0) to (1, 1, 1)   ->  12 to 13
    oTransition.set(12, 13);
    oGameState12.addTransition(oTransition);
    
    // (1, 2, 0) to (1, 2, 1)   ->  15 to 16
    oTransition.set(15, 16);
    oGameState15.addTransition(oTransition);
    
    // (2, 0, 0) to (2, 0, 1)   ->  18 to 19
    oTransition.set(18, 19);
    oGameState18.addTransition(oTransition);
    
    // (2, 0, 0) to (2, 1, 0)   ->  18 to 21
    oTransition.set(18, 21);
    oGameState18.addTransition(oTransition);
    
    // (2, 0, 1) to (2, 1, 1)   ->  19 to 22
    oTransition.set(19, 22);
    oGameState19.addTransition(oTransition);
    
    // (2, 0, 2) to (2, 1, 2)   ->  20 to 23
    oTransition.set(20, 23);
    oGameState20.addTransition(oTransition);
    
    // (2, 1, 0) to (2, 1, 1)   ->  21 to 22
    oTransition.set(21, 22);
    oGameState21.addTransition(oTransition);
    
    // (2, 2, 0) to (2, 2, 1)   ->  24 to 25
    oTransition.set(24, 25);
    oGameState24.addTransition(oTransition);
    
    LOG4CXX_INFO(logger, oGameState0.showData());
    LOG4CXX_INFO(logger, oGameState1.showData());
    LOG4CXX_INFO(logger, oGameState2.showData());
    LOG4CXX_INFO(logger, oGameState3.showData());
    LOG4CXX_INFO(logger, oGameState4.showData());
    LOG4CXX_INFO(logger, oGameState5.showData());
    LOG4CXX_INFO(logger, oGameState6.showData());
    LOG4CXX_INFO(logger, oGameState7.showData());
    LOG4CXX_INFO(logger, oGameState8.showData());
    LOG4CXX_INFO(logger, oGameState9.showData());
    LOG4CXX_INFO(logger, oGameState10.showData());
    LOG4CXX_INFO(logger, oGameState11.showData());
    LOG4CXX_INFO(logger, oGameState12.showData());
    LOG4CXX_INFO(logger, oGameState13.showData());
    LOG4CXX_INFO(logger, oGameState14.showData());
    LOG4CXX_INFO(logger, oGameState15.showData());
    LOG4CXX_INFO(logger, oGameState16.showData());
    LOG4CXX_INFO(logger, oGameState17.showData());
    LOG4CXX_INFO(logger, oGameState18.showData());
    LOG4CXX_INFO(logger, oGameState19.showData());
    LOG4CXX_INFO(logger, oGameState20.showData());
    LOG4CXX_INFO(logger, oGameState21.showData());
    LOG4CXX_INFO(logger, oGameState22.showData());
    LOG4CXX_INFO(logger, oGameState23.showData());
    LOG4CXX_INFO(logger, oGameState24.showData());
    LOG4CXX_INFO(logger, oGameState25.showData());
    LOG4CXX_INFO(logger, oGameState26.showData());
    
    addGameState(oGameState0);
    addGameState(oGameState1);
    addGameState(oGameState2);
    addGameState(oGameState3);
    addGameState(oGameState4);
    addGameState(oGameState5);  
    addGameState(oGameState6);
    addGameState(oGameState7);
    addGameState(oGameState8);
    addGameState(oGameState9);
    addGameState(oGameState10);
    addGameState(oGameState11);  
    addGameState(oGameState12);
    addGameState(oGameState13);
    addGameState(oGameState14);
    addGameState(oGameState15);
    addGameState(oGameState16);
    addGameState(oGameState17);  
    addGameState(oGameState18);
    addGameState(oGameState19);
    addGameState(oGameState20);
    addGameState(oGameState21);
    addGameState(oGameState22);
    addGameState(oGameState23);  
    addGameState(oGameState24);
    addGameState(oGameState25);
    addGameState(oGameState26);
    
    LOG4CXX_INFO(logger, "tic tac toe built");
    
}


}