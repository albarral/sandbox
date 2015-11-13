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
    bestChance = eCHANCES_ZERO;     
}

void Strategy::attackRandom(std::vector<int> listEmptyCells)
{
    // we start the check with zero chances
    bestChance = Strategy::eCHANCES_ZERO;  

    // no attack if line is closed
    if (listEmptyCells.size() == 0)
        return;    

    // Choose one of the empty cells randomly
    int randNum = rand() % listEmptyCells.size();
    bestMove = listEmptyCells.at(randNum);
    bestChance = Strategy::eCHANCES_LOW;
}


// selects the attack move based on a simple predefined knowledge
void Strategy::attack(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells)
{    
    // we start the check with zero chances
    bestChance = Strategy::eCHANCES_ZERO;  

    // no attack if line is closed
    if (listEmptyCells.size() == 0)
        return;    
    
    // open line & free of others
    if (numEmpties > 0 && numOthers == 0)
    {
        switch (numMines)
        {               
            // 0 mine (3 empty) -> medium chances (first move)
            case 0:
                bestChance = Strategy::eCHANCES_LOW;
                break;
            // 1 mine -> good chances
            case 1:
                bestChance = Strategy::eCHANCES_HIGH;
                break;
            // 2 mine -> winner move
            case 2:
                bestChance = Strategy::eCHANCES_WINNER;
                break;                    
        }          
        
        // select first empty cell in the line
        bestMove = listEmptyCells.at(0);        
    }
}

}
}