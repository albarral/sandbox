#ifndef __SAM_STRATEGY_H
#define __SAM_STRATEGY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

namespace sam
{    
namespace player
{     
// This class implements a simple strategy to select the best cell move based on predefined knowledge .
// It also provides an option for random selection among the available cells in the line.
class Strategy 
{
public:        
    // Chances to win when selecting a cell from a given line (row, column or diagonal) 
    enum eChance
    {
        eREWARD_ZERO,        // no chances: closed line or open line - some others
        eREWARD_LOW,         // low chances: open line - all empty
        eREWARD_HIGH,        // high changes: open line - 1 mine + 2 empties
        eREWARD_MAX     // winner move: open line - 2 mines + 1 empty
    };

private:
    static log4cxx::LoggerPtr logger;
    
public:
    Strategy();

    // selects the attack move based on a simple predefined knowledge
    float attack(int numMines, int numOthers, int numEmpties);
    // selects the defense move based on a simple predefined knowledge
    float defend(int numMines, int numOthers, int numEmpties);
    // random attack
    float randomAttack();
    // random defense
    float randomDefense();
};
}
}
#endif

