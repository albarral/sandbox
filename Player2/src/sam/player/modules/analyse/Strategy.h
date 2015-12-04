#ifndef __SAM_STRATEGY_H
#define __SAM_STRATEGY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
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
        eCHANCES_ZERO,        // no chances: closed line or open line - some others
        eCHANCES_LOW,         // low chances: open line - all empty
        eCHANCES_HIGH,        // high changes: open line - 1 mine + 2 empties
        eCHANCES_WINNER     // winner move: open line - 2 mines + 1 empty
    };

private:
    static log4cxx::LoggerPtr logger;
    int bestMove;           // selected cell for attack move (cell position in the board line)
    int bestChance;        // best chance for attach move
    
public:
    Strategy();

    int getBestMove() {return bestMove;}
    int getBestChance() {return bestChance;}
        
    // selects the attack move based on a simple predefined knowledge
    void attack(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells);
    // selects the attack move randomly among the available empty cells
    void moveRandom(std::vector<int> listEmptyCells);
    
private:    
    // sets values to invalid attack (no chance, no move)
    void setInvalidAttack();
};
}
}
#endif

