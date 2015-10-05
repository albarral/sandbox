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
    rewardAttack = 0;
    rewardDefense = 0;
    dVictory = 0;
    dDefeat = 0;   
}

}