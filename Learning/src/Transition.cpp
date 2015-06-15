/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Transition.h"
#include "State.h"
#include "Connection.h"
#include "types/TransitionType.h"

namespace sam 
{
Transition::Transition() 
{
    ID = 0;
    desc = "";
    taskID = 0;
    stateID = 0;
    nextState = 0;
    cost = 0; // 0.0 or 0f
    Q = 0; // 0.0 or 0f
}

void Transition::set(int stateID, int nextState, int type)
{    
    this->stateID = stateID;
    this->nextState = nextState;
          
    TransitionType oType;
    oType.set(type);
    this->desc = oType.getDesc();    
    this->cost = oType.getCost();
}

void Transition::loadFromMemo(Database* pDatabase, sql::Connection *con)
{
    std::string sel = "SELECT * FROM TAB_TRANSITIONS WHERE taskID = " + std::to_string(taskID)
            + " AND stateID = " + std::to_string(stateID) + " AND transID = " + std::to_string(ID);
    sql::ResultSet *res = pDatabase->select(sel, con);
    
    while (res->next())
    {
        desc = res->getString("description");
        nextState = res->getInt("nextState");
        cost = res->getDouble("cost"); //El getFloat da problemas
        Q = res->getDouble("q"); //El getFloat da problemas
    }
}

void Transition::storeInMemo(Database* pDatabase, sql::Connection *con)
{
    std::string insert = "INSERT INTO TAB_TRANSITIONS (transID, description, taskID, stateID, nextState, cost, q) "
            "VALUES (" + std::to_string(ID) + ", ' " + desc + " ', " + std::to_string(taskID) 
            + ", " + std::to_string(stateID) + ", " + std::to_string(nextState) + ", " + std::to_string(cost)
            + ", " + std::to_string(Q) + ")";   
    pDatabase->update(insert, con);
}

void Transition::upDateInMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_TRANSITIONS SET description= ' " + desc +
            " ' nextState = " + std::to_string(nextState) + ", cost = " + std::to_string(cost) + ", q = " + 
            std::to_string(Q) + " WHERE transID = " + std::to_string(ID)
            + " AND taskID= " + std::to_string(taskID) + " AND stateID= " + std::to_string(stateID);
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void Transition::deleteFromMemo(Database* pDatabase)
{
    sql::Connection *con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_TRANSITIONS WHERE transID= " + std::to_string(ID);
            + " AND taskID= " + std::to_string(taskID) + " AND stateID= " + std::to_string(stateID);
    pDatabase->update(deleteDB, con);   
    con->commit();
    pDatabase->closeConnectionDB();
}

// computes the cost of traversing the connection
float Transition::computeCost()
{
    if (cost == 0)
    {
        Connection oConnection;
        cost = oConnection.computeCost();
    }
    
    return cost;
}

std::string Transition::showData()
{
    std::string data = ">> transition " + std::to_string(ID) + ": " + std::to_string(stateID) + "->" + std::to_string(nextState) + ", " + desc;
    return data;
}

}