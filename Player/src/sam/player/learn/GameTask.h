#ifndef __SAM_PLAYER_GAMETASK_H
#define __SAM_PLAYER_GAMETASK_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/player/learn/GameState.h"
#include "sam/utilsDB/Database.h"

namespace sam 
{
namespace player
{     
class GameTask
{
private:
    int ID;
    std::string desc;
    int type;
    utilsDB::Database oDatabase;
    std::vector<GameState> listGameStates;
    
public:
    GameTask();
    
    int getID() {return ID;};
    void setID(int value) {ID = value;};
    
    std::string getDesc() {return desc;};
    void setDesc(std::string value) {desc = value;};
    
    int getType() {return type;};
    void setType(int value) {type = value;};
    
    std::vector<GameState>& getListGameStates() {return listGameStates;}; 
    void addGameState(GameState& oGameState);
    
    void storeInMemo2();
    void loadFromMemo2();
    void upDateInMemo2();
    void deleteFromMemo2();
    void storeQ();
    void reset();
    
    std::string showData();
    
private:    
    void gameStatesFromMemo(sql::Connection* con);
    void loadGameStates(sql::Connection* con, utilsDB::Database* pDatabase);
    void storeGameStates(sql::Connection* con, utilsDB::Database* pDatabase);
};
}
}

#endif
