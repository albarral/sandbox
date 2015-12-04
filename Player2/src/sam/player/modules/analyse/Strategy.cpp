/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/analyse/Strategy.h"

namespace sam
{    
namespace player
{             
log4cxx::LoggerPtr Strategy::logger(log4cxx::Logger::getLogger("sam.player"));

Strategy::Strategy() 
{
    setInvalidAttack();
    setInvalidDefense();
}

void Strategy::randomAttack(std::vector<int> listEmptyCells)
{
    setInvalidAttack();
    
    // no attack if line is closed
    if (listEmptyCells.size() == 0)
        return;    

    // Choose one of the empty cells randomly
    int randNum = rand() % listEmptyCells.size();
    attackCell = listEmptyCells.at(randNum);
    // low chances if you attack randomly
    attackReward = Strategy::eREWARD_LOW;
}


void Strategy::randomDefense(std::vector<int> listEmptyCells)
{
    setInvalidDefense();
    
    // no defense if line is closed
    if (listEmptyCells.size() == 0)
        return;    

    // Choose one of the empty cells randomly
    int randNum = rand() % listEmptyCells.size();
    defenseCell = listEmptyCells.at(randNum);
    // low chances if you defend randomly
    defenseReward = Strategy::eREWARD_LOW;
}

// selects the attack move based on a simple predefined knowledge
void Strategy::attack(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells)
{
    setInvalidAttack();    
    
    // no attack if line is closed
    if (listEmptyCells.size() == 0)
        return;    
    
    // open line & free of others
    if (numOthers == 0)
    {
        switch (numMines)
        {               
            // 0 mine (3 empty) -> medium chances (first move)
            case 0:
                attackReward = Strategy::eREWARD_LOW;
                break;
            // 1 mine -> good chances
            case 1:
                attackReward = Strategy::eREWARD_HIGH;
                break;
            // 2 mine -> winner move
            case 2:
                attackReward = Strategy::eREWARD_MAX;
                break;                    
        }                  
    }
    // open line, but with others
    else 
        attackReward = Strategy::eREWARD_ZERO;          

    // select first empty cell in the line
    attackCell = listEmptyCells.at(0);        
}

// selects the attack move based on a simple predefined knowledge
void Strategy::defend(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells)
{
    setInvalidDefense();
    
    // no defense if line is closed
    if (listEmptyCells.size() == 0)
        return;    
    
    // open line & free of mines
    if (numMines == 0)
    {
        switch (numOthers)
        {               
            // 0 mine (3 empty) -> medium chances (first move) ??
            case 0:
                defenseReward = Strategy::eREWARD_LOW;
                break;
            // 1 mine -> good chances ??
            case 1:
                defenseReward = Strategy::eREWARD_HIGH;
                break;
            // 2 mine -> winner move ??
            case 2:
                defenseReward = Strategy::eREWARD_MAX;
                break;                    
        }                  
    }
    // open line, but with mines already
    else 
        defenseReward = Strategy::eREWARD_ZERO;          

    // select first empty cell in the line
    defenseCell = listEmptyCells.at(0);        
}


void Strategy::setInvalidAttack()
{
    attackReward = -1;
    attackCell = -1;    
}

void Strategy::setInvalidDefense()
{
    defenseReward = -1;
    defenseCell = -1;    
}

}
}