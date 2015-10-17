/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Transition.h"
#include "State.h"
#include "nav/Connection.h"

namespace sam 
{
Transition::Transition() 
{
    ID = 0;
    desc = "";
    taskID = 0;
    stateID = 0;
    nextState = 0;
    Q = 0; // 0.0 or 0f
}

void Transition::set(int stateID, int nextState)
{    
    this->stateID = stateID;
    this->nextState = nextState;
}

void Transition::loadFromMemo(Database* pDatabase, sql::Connection* con)
{
    std::string sel = "SELECT * FROM TAB_TRANSITIONS WHERE taskID = " + std::to_string(taskID)
            + " AND stateID = " + std::to_string(stateID) + " AND transID = " + std::to_string(ID);
    sql::ResultSet* res = pDatabase->select(sel, con);
    
    while (res->next())
    {
        desc = res->getString("description");
        nextState = res->getInt("nextState");
        Q = res->getDouble("Q");
    }
}

void Transition::storeInMemo(Database* pDatabase, sql::Connection* con)
{
    std::string insert = "INSERT INTO TAB_TRANSITIONS (transID, description, taskID, stateID, nextState, cost,"
            " Q) VALUES (" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(taskID) 
            + ", " + std::to_string(stateID) + ", " + std::to_string(nextState) + ", " + std::to_string(Q) + ")";   
    pDatabase->update(insert, con);
}

void Transition::upDateInMemo(Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_TRANSITIONS SET description= ' " + desc +
            " ' nextState = " + std::to_string(nextState) + ", Q = " + 
            std::to_string(Q)  + " WHERE transID = " + std::to_string(ID)
            + " AND taskID= " + std::to_string(taskID) + " AND stateID= " + std::to_string(stateID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Transition::deleteFromMemo(Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_TRANSITIONS WHERE transID= " + std::to_string(ID);
            + " AND taskID= " + std::to_string(taskID) + " AND stateID= " + std::to_string(stateID);
    pDatabase->update(deleteDB, con);   
    con->commit();
    pDatabase->closeConnectionDB();
}

void Transition::storeQ(Database* pDatabase, sql::Connection* con)
{
    std::string storeQ = "UPDATE TAB_TRANSITIONS SET Q= " + std::to_string(Q) + 
            " WHERE transID= " + std::to_string(ID) + " AND taskID= " 
            + std::to_string(taskID) + " AND stateID= " + std::to_string(stateID);   
    pDatabase->update(storeQ, con);
}

std::string Transition::toString()
{
    return ("Transition: [taskID=" + std::to_string(taskID) + ", stateID=" + std::to_string(stateID) + ", ID=" + std::to_string(ID) 
            + ", nextState=" + std::to_string(nextState) + ", Q=" + std::to_string((int)Q) + "]");
}

}