#ifndef __SAM_PLAYER_ACTIONS_H
#define __SAM_PLAYER_ACTIONS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "sam/player/learn/GameState.h"

namespace sam
{  
namespace player
{     
// Class used to deduce proper Player actions for given state transitions.
class PlayerActions 
{  
public:
    enum eAction  
    {
        eSELECT_FIRST,         // select first cell in a line
        eSELECT_SECOND,     // select second cell in a line
        eSELECT_THIRD         // select third cell in a line  
    };
    
private:
    std::vector<int> listActions;    // list of actions needed to perform a given transition
    
public:
    PlayerActions();
    
    // deduce needed actions to perform the specified transition
    int getActions4Transition(GameState& oGameState1, GameState& oGameState2);
    
    // applies deduced action to the given row, column or diagonal
    void applyAction2Row (int row, int& x, int& y);
    void applyAction2Column (int col, int& x, int& y);
    void applyAction2Diagonal (int lineType, int& x, int& y);

    std::vector<int>& getListActions() {return listActions;}    
    
};
}
}
#endif

