/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "GameTask.h"
#include "GameState.h"

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
    loadFromMemo2();
    
    describeTask();   
}

void GameTask::addGameState(GameState& oGameState)
{
    listGameStates.push_back(oGameState);
}

void GameTask::storeInMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB(); 
    Database* pDatabase2 = &oDatabase;
    //Store the GameStates
    std::vector<GameState>::iterator it_state = listGameStates.begin();
    std::vector<GameState>::iterator it_end = listGameStates.end();
    while (it_state != it_end)
    {
        it_state->storeInMemo2(pDatabase2, con);
        it_state++;	
    }
    con->commit();
    oDatabase.closeConnectionDB();
}

void GameTask::loadFromMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB(); 
    Database* pDatabase2 = &oDatabase;
    gameStatesFromMemo(con);
    
    //load the GameStates
    std::vector<GameState>::iterator it_state = listGameStates.begin();
    std::vector<GameState>::iterator it_end = listGameStates.end();
    while (it_state != it_end)
    {
        it_state->loadFromMemo2(pDatabase2, con);
        it_state++;
    }
}

void GameTask::gameStatesFromMemo(sql::Connection* con)
{
    std::string sel = "SELECT stateID FROM TAB_STATES_PLAYER WHERE taskID = " + std::to_string(getID());
    sql::ResultSet* res = oDatabase.select(sel, con);
    
    while (res->next())
    {
        GameState oGameState;
        oGameState.setTaskID(getID());
        int id = res->getInt("stateID");
        oGameState.setID(id);
        addGameState(oGameState);
    }    
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