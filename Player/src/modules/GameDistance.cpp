/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "GameDistance.h"

namespace sam
{    
GameDistance::GameDistance() 
{
    gameCells = 3;
}

int GameDistance::computeDistance2Victory(int mines, int others)
{
    //calculate dVictory ->  dVictory = others * 2 + empties
    return others * 2 + (gameCells - mines - others);
}

int GameDistance::computeDistance2Defeat(int mines, int others)
{
    //calculate dDefeat ->  dDefeat = mines * 2 + empties
    return mines * 2 + (gameCells - mines - others);
}

}