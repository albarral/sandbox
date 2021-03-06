#ifndef __SAM_GAMESTATE_H
#define __SAM_GAMESTATE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "State.h"

namespace sam 
{
class GameState : public State
{
private:
    int cells[3];
    int numMines;       // number of cells marked as mine
    int numOthers;      // number of cells marked as others'
    
public:
    GameState();
    
    int* getCells() {return cells;}
    
    int getNumMines() {return numMines;};   
    int getNumOthers() {return numOthers;};   
    
    void set(int cell1, int cell2, int cell3, int mines, int others);
    
    void loadFromMemo2(Database* pDatabase, sql::Connection* con);
    void storeInMemo2(Database* pDatabase, sql::Connection* con);
    void upDateInMemo2(Database* pDatabase);
    void deleteFromMemo2(Database* pDatabase);
    
    std::string toString();
    std::string toStringBrief();
};
}

#endif
