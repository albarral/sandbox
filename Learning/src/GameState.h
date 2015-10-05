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
    int rewardAttack;
    int rewardDefense;
    int dVictory; //Temporal    Distance to victory
    int dDefeat; //Temporal     Distance to defeat
    
public:
    GameState();
    
    int getNumMines() {return numMines;};   
    int getNumOthers() {return numOthers;};   
    
    int getRewardAttack() {return rewardAttack;};
    void setRewardAttack(int value)  {rewardAttack = value;};
    
    int getRewardDefense() {return rewardDefense;};
    void setRewardDefense(int value)  {rewardDefense = value;};
    
    int getDVictory() {return dVictory;};
    void setDVictory(int value)  {dVictory = value;};
    
    int getDDefeat() {return dDefeat;};
    void setDDefeat(int value)  {dDefeat = value;};

};
}

#endif
