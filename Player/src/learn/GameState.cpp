/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "GameState.h"

namespace sam 
{
GameState::GameState() 
{
    numMines = 0;
    numOthers = 0;
}

void GameState::set(int cell1, int cell2, int cell3, int mines, int others)
{
    cells[0] = cell1;
    cells[1] = cell2;
    cells[2] = cell3;
    numMines = mines;
    numOthers = others;
}

void GameState::loadFromMemo2(Database* pDatabase, sql::Connection* con)
{
    std::string sel = "SELECT * FROM TAB_GAME_STATES WHERE taskID = " + std::to_string(getTaskID())
            + " AND stateID = " + std::to_string(getID());
    sql::ResultSet* res = pDatabase->select(sel, con);
      
    while (res->next())
    {
        State::desc = res->getString("description");
        State::reward = res->getDouble("reward");
        cells[0] = res->getInt("cell0");
        cells[1] = res->getInt("cell1");
        cells[2] = res->getInt("cell2");
        numMines = res->getInt("numMines");
        numOthers = res->getInt("numOthers");
    }
    
    State::transitionsFromMemo(pDatabase, con);
    State::loadTransitions(pDatabase, con);
}

void GameState::storeInMemo2(Database* pDatabase, sql::Connection* con)
{
    std::string insertDB = "INSERT INTO TAB_GAME_STATES (stateID, taskID, description, reward, cell0, cell1, "
            "cell2, numMines, numOthers) VALUES (" + std::to_string(getID()) + ", " + std::to_string(getTaskID()) 
            + ", ' " + desc + " ', " + std::to_string(reward) + ", " + std::to_string(cells[0]) 
            + ", " + std::to_string(cells[1]) + + ", " + std::to_string(cells[2]) 
            + ", " + std::to_string(numMines) + + ", " + std::to_string(numOthers) + ")";    
    pDatabase->update(insertDB, con);
    
    State::storeTransitions(pDatabase, con);
}

void GameState::upDateInMemo2(Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string update = "UPDATE TAB_STATES_PLAYER SET description = ' " + desc + " ' ,reward = " 
            + std::to_string(reward) + " ,cell0 = " + std::to_string(cells[0]) + " ,cell1 = " 
            + std::to_string(cells[1]) + " ,cell2 = " + std::to_string(cells[2]) + " ,numMines = " 
            + std::to_string(numMines) + " ,numOthers = " + std::to_string(numOthers) + " WHERE stateID = " 
            + std::to_string(getID()) + " AND taskID= " + std::to_string(getTaskID());
    pDatabase->update(update, con);
    con->commit();
    pDatabase->closeConnectionDB();
}

void GameState::deleteFromMemo2(Database* pDatabase)
{
    sql::Connection* con = pDatabase->getConnectionDB();
    std::string deleteDB = "DELETE FROM TAB_STATES_PLAYER WHERE stateID= "+ std::to_string(getID());
            + " AND taskID= " + std::to_string(getTaskID());
    pDatabase->update(deleteDB, con);    
    con->commit();
    pDatabase->closeConnectionDB();
}

std::string GameState::toString()
{
  return ("GameState: [taskID=" + std::to_string(taskID) + ", ID=" + std::to_string(ID) +
          ", cells[]=(" + std::to_string(cells[0]) + "," + std::to_string(cells[1]) + "," + std::to_string(cells[2]) + ")" +
          ", reward=" + std::to_string((int)reward) + "]");  
}

std::string GameState::toStringBrief()
{
  return ("state " + std::to_string(ID) + ": (" + std::to_string(cells[0]) + "," + std::to_string(cells[1]) + "," + std::to_string(cells[2]) + ")" +
          " rwd=" + std::to_string((int)reward));  
}
}