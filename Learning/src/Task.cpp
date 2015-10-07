/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Task.h"
#include "GameState.h"

namespace sam 
{
Task::Task() 
{
    reset();
}

void Task::addState(State& oState)
{
    listStates.push_back(oState);
}

void Task::loadFromMemo()
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string sel = "SELECT * FROM TAB_TASKS WHERE taskID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
       
    while (res->next())
    {
        ID = res->getInt("taskID");
        desc = res->getString("description");
        type = res->getInt("type");
    }
    
    statesFromMemo(con);
    loadStates(con);
    
    pDatabase->closeConnectionDB();
}

void Task::storeInMemo()
{   
    sql::Connection* con = pDatabase->getConnectionDB(); 
    std::string insert = "INSERT INTO TAB_TASKS (taskID, description, type) VALUES "
        "(" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(type) + ")";    
    pDatabase->update(insert, con);
        
    storeStates(con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Task::upDateInMemo()
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_TASKS SET description = ' " + desc + " ', type = " 
            + std::to_string(type) + " WHERE taskID= " + std::to_string(ID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Task::deleteFromMemo()
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_TASKS WHERE taskID= " + std::to_string(ID);
    pDatabase->update(deleteDB, con);  
    con->commit();
    pDatabase->closeConnectionDB();
}

void Task::storeQ()
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::vector<State>::iterator it_state = listStates.begin();
    std::vector<State>::iterator it_end = listStates.end();
    while (it_state != it_end)
    {
        it_state->storeQ(pDatabase, con);
        it_state++;
    }
    con->commit();
    pDatabase->closeConnectionDB();
}

void Task::statesFromMemo(sql::Connection* con)
{
    std::string sel = "SELECT stateID FROM TAB_STATES WHERE taskID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
    
    while (res->next())
    {
        State oState;
        oState.setTaskID(ID);
        int id = res->getInt("stateID");
        oState.setID(id);
        addState(oState);
    }    
}

void Task::loadStates(sql::Connection* con)
{
    std::vector<State>::iterator it_state = listStates.begin();
    std::vector<State>::iterator it_end = listStates.end();
    while (it_state != it_end)
    {
        it_state->loadFromMemo(pDatabase, con);
        it_state++;
    }
}

void Task::storeStates(sql::Connection* con)
{
    std::vector<State>::iterator it_state = listStates.begin();
    std::vector<State>::iterator it_end = listStates.end();
    while (it_state != it_end)
    {
        it_state->storeInMemo(pDatabase, con);
        it_state++;	
    }

//    std::vector<GameState>::iterator it_state = listGameStates.begin();
//    std::vector<GameState>::iterator it_end = getListGameStates().end();
//    while (it_state != it_end)
//    {
//        it_state->storeInMemo(pDatabase, con);
//        it_state++;
//    } 
}

void Task::reset()
{
    ID = 0;
    desc = "";
    type = 0;
    listStates.clear();    
}

std::string Task::showData()
{
    std::string data = "task " + std::to_string(ID) + ": " + desc;    
    return data;
}

}