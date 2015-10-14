/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "PlayerActions.h"
#include "data/GameBoard.h"

namespace sam
{    
PlayerActions::PlayerActions() 
{
    listActions.clear();
}


// deduce needed actions to perform the specified transition
int PlayerActions::getActions4Transition(GameState& oGameState1, GameState& oGameState2)
{
    int action;
    
    // reset actions list
    listActions.clear();
    int* pcells1 = oGameState1.getCells();
    int* pcells2 = oGameState2.getCells();
    
    // compare pairs of cells ...
    for (int i=0; i<GameBoard::cells4Line; i++)
    {
        // and select those that change
        if (pcells1[i] != pcells2[i])
        {
            switch (i)
            {
                case 0: 
                    action = eSELECT_FIRST;
                    break;
                case 1: 
                    action = eSELECT_SECOND;
                    break;
                case 2: 
                    action = eSELECT_THIRD;
                    break;                    
            }                       
        }
        
        listActions.push_back(action);        
    }
    
    return listActions.size();
}

// x means column, y means row
void PlayerActions::applyAction2Row(int row, int& x, int& y)
{    
    x = listActions.at(0);
    y = row;
}

void PlayerActions::applyAction2Column(int col, int& x, int& y)
{    
    x = col;
    y = listActions.at(0);
}

void PlayerActions::applyAction2Diagonal(int diag, int& x, int& y)
{
    if (diag == 1)
    {
        x = y = listActions.at(0);
    }
    else if (diag == 2)
    {
        x = 2 - listActions.at(0);
        y = listActions.at(0);
    }
}
}