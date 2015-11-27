/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "sam/learn/State.h"
#include "sam/learn/Task.h"

namespace sam 
{
namespace learn
{
State::State() 
{
    ID = 0;
    desc = "";
    taskID = 0;
    reward = 0; // 0.0 or 0f
}

void State::addTransition(Transition& oTransition)
{
    // transition ID is assigned automatically
    oTransition.setID(listTransitions.size());
    listTransitions.push_back(oTransition);
}

void State::loadFromMemo(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::string sel = "SELECT * FROM TAB_STATES WHERE taskID = " + std::to_string(taskID)
            + " AND stateID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
      
    while (res->next())
    {
        desc = res->getString("description");
        reward = res->getDouble("reward");
    }
    
    transitionsFromMemo(pDatabase, con);
    loadTransitions(pDatabase, con);
}

void State::storeInMemo(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::string insertDB = "INSERT INTO TAB_STATES (stateID, description, taskID, reward) "
            "VALUES (" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(taskID) + ", " 
            + std::to_string(reward) + ")";    
    pDatabase->update(insertDB, con);

    storeTransitions(pDatabase, con);
}

void State::upDateInMemo(utilsDB::Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_STATES SET description = ' " + desc + " ' ,reward = " + std::to_string(reward)
    + " WHERE stateID = " + std::to_string(ID) 
    + " AND taskID= " + std::to_string(taskID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void State::deleteFromMemo(utilsDB::Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_STATES WHERE stateID= "+ std::to_string(ID);
            + " AND taskID= " + std::to_string(taskID);
    pDatabase->update(deleteDB, con);    
    con->commit();
    pDatabase->closeConnectionDB();
}

void State::storeQ(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::vector<Transition>::iterator it_transition = listTransitions.begin();
    std::vector<Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {
        it_transition->storeQ(pDatabase, con);
        it_transition++;	
    }
}

void State::transitionsFromMemo(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::string sel = "SELECT transID FROM TAB_TRANSITIONS WHERE taskID = " + std::to_string(taskID)
            + " AND stateID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
    
    while (res->next())
    {
        Transition oTransition;
        oTransition.setTaskID(taskID);
        oTransition.setStateID(ID);
        int id = res->getInt("transID");
        oTransition.setID(id);
        addTransition(oTransition);
    }
}

void State::loadTransitions(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::vector<Transition>::iterator it_transition = listTransitions.begin();
    std::vector<Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {
        it_transition->loadFromMemo(pDatabase, con);
        it_transition++;	
    }
}

void State::storeTransitions(utilsDB::Database* pDatabase, sql::Connection* con)
{
    std::vector<Transition>::iterator it_transition = listTransitions.begin();
    std::vector<Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {
        it_transition->storeInMemo(pDatabase, con);
        it_transition++;	
    }
}

std::string State::showData()
{
    std::string data = "> state " + std::to_string(ID) + ": " + desc;    
    return data;
}

}
}
