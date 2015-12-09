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
}

float Strategy::randomAttack()
{
    // low chances if you attack randomly
    return Strategy::eREWARD_LOW;
}


float Strategy::randomDefense()
{
    // low chances if you defend randomly
    return Strategy::eREWARD_LOW;
}

// selects the attack move based on a simple predefined knowledge
float Strategy::attack(int numMines, int numOthers, int numEmpties)
{
    float attackReward;
    
    // no attack if line is closed
    if (numEmpties == 0)
        return Strategy::eREWARD_ZERO;    
    
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

    return attackReward;
}

// selects the attack move based on a simple predefined knowledge
float Strategy::defend(int numMines, int numOthers, int numEmpties)
{
    float defenseReward;
    
    // no defense if line is closed
    if (numEmpties == 0)
        return Strategy::eREWARD_ZERO;    
    
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

    return defenseReward;        
}

}
}