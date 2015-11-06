/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "sam/player/learn/GameTask.h"

namespace sam 
{
namespace player
{     
GameTask::GameTask() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    reset();
}

void GameTask::addGameState(GameState& oGameState)
{
    listGameStates.push_back(oGameState);
}

void GameTask::storeInMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB(); 

    std::string insert = "INSERT INTO TAB_TASKS (taskID, description, type) VALUES "
        "(" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(type) + ")";    
    oDatabase.update(insert, con);
        
    storeGameStates(con, &oDatabase);
    con->commit();
    oDatabase.closeConnectionDB();
}

void GameTask::loadFromMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB(); 
    std::string sel = "SELECT * FROM TAB_TASKS WHERE taskID = " + std::to_string(ID);
    sql::ResultSet* res = oDatabase.select(sel, con);
       
    while (res->next())
    {
        ID = res->getInt("taskID");
        desc = res->getString("description");
        type = res->getInt("type");
    }
    
    gameStatesFromMemo(con);
    loadGameStates(con, &oDatabase);
    
    oDatabase.closeConnectionDB();   
}

void GameTask::upDateInMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB();
    std::string update = "UPDATE TAB_TASKS SET description = ' " + desc + " ', type = " 
            + std::to_string(type) + " WHERE taskID= " + std::to_string(ID);
    oDatabase.update(update, con);
    con->commit();
    oDatabase.closeConnectionDB();
}

void GameTask::deleteFromMemo2()
{
    sql::Connection* con = oDatabase.getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_TASKS WHERE taskID= " + std::to_string(ID);
    oDatabase.update(deleteDB, con);  
    con->commit();
    oDatabase.closeConnectionDB();
}

void GameTask::storeQ()
{
    sql::Connection* con = oDatabase.getConnectionDB();
    std::vector<GameState>::iterator it_state = listGameStates.begin();
    std::vector<GameState>::iterator it_end = listGameStates.end();
    while (it_state != it_end)
    {
        it_state->storeQ(&oDatabase, con);
        it_state++;
    }
    con->commit();
    oDatabase.closeConnectionDB();
}

void GameTask::gameStatesFromMemo(sql::Connection* con)
{
    std::string sel = "SELECT stateID FROM TAB_GAME_STATES WHERE taskID = " + std::to_string(getID());
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

void GameTask::loadGameStates(sql::Connection* con, utils::Database* pDatabase)
{
    std::vector<GameState>::iterator it_state = listGameStates.begin();
    std::vector<GameState>::iterator it_end = listGameStates.end();
    while (it_state != it_end)
    {
        it_state->loadFromMemo2(pDatabase, con);
        it_state++;
    }
}

void GameTask::storeGameStates(sql::Connection* con, utils::Database* pDatabase)
{
    std::vector<GameState>::iterator it_state = listGameStates.begin();
    std::vector<GameState>::iterator it_end = listGameStates.end();
    while (it_state != it_end)
    {
        it_state->storeInMemo2(pDatabase, con);
        it_state++;	
    }
}

void GameTask::reset()
{
    ID = 0;
    desc = "";
    type = 0;
    listGameStates.clear();    
}

std::string GameTask::showData()
{
    std::string data = "Task: [ID=" + std::to_string(ID) + ", desc=" + desc + "]";    
    return data;
}

}
}