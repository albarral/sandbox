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

    loadFromMemo();
    
    describeTask();   
}

void GameTask::addGameState(GameState& oGameState)
{
    listGameStates.push_back(oGameState);
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

    // describe its transitions
    std::vector<Transition>::iterator it_trans = pGameState->getListTransitions().begin();
    std::vector<Transition>::iterator it_end = pGameState->getListTransitions().end();
    while (it_trans != it_end)
    {
        LOG4CXX_INFO(logger, it_trans->showData());
        it_trans++;
    }
}   

}