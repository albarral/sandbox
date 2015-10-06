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
    dVictory = 0;
    dDefeat = 0;   
}

void GameState::set(int cell1, int cell2, int cell3, int mines, int others)
{
    cells[0] = cell1;
    cells[1] = cell2;
    cells[2] = cell3;
    numMines = mines;
    numOthers = others;
}

}