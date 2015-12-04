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
        eREWARD_ZERO,        // no chances: closed line or open line - some others
        eREWARD_LOW,         // low chances: open line - all empty
        eREWARD_HIGH,        // high changes: open line - 1 mine + 2 empties
        eREWARD_MAX     // winner move: open line - 2 mines + 1 empty
    };

private:
    static log4cxx::LoggerPtr logger;
    int attackCell;           // selected cell for attack move (cell position in the board line)
    int attackReward;        // best chance for attach move
    int defenseCell;           // selected cell for attack move (cell position in the board line)
    int defenseReward;        // best chance for attach move
    
public:
    Strategy();

    int getAttackElement() {return attackCell;}
    int getAttackChance() {return attackReward;}
    int getDefenseElement() {return defenseCell;}
    int getDefenseChance() {return defenseReward;}
        
    // selects the attack move based on a simple predefined knowledge
    void attack(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells);
    // selects the defense move based on a simple predefined knowledge
    void defend(int numMines, int numOthers, int numEmpties, std::vector<int> listEmptyCells);
    // random attack
    void randomAttack(std::vector<int> listEmptyCells);
    // random defense
    void randomDefense(std::vector<int> listEmptyCells);
    
private:    
    // sets values to invalid attack (no chance, no move)
    void setInvalidAttack();
    // sets values to invalid attack (no chance, no move)
    void setInvalidDefense();
};
}
}
#endif

