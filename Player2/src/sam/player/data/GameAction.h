#ifndef __SAM_PLAYER_GAMEACTION_H
#define __SAM_PLAYER_GAMEACTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

#include "sam/player/utils/GameMove.h"

namespace sam
{  
namespace player
{     
// (shared data) This class represents a game action.
// It holds the best attack & defense moves for the present game board configuration.
// mutex protected
class GameAction 
{  
private:
    std::mutex mutex;
    GameMove oAttackMove;         // attack move   
    GameMove oDefenseMove;      // defense move
    
public:
    GameAction();
    
    void reset();
        
    void updateAttackInfo(GameMove& oMove);
    void updateDefenseInfo(GameMove& oMove);
    
    float getAttackMoveReward();
    float getDefenseMoveReward();
    
    GameMove getAttackMoveCopy();
    GameMove getDefenseMoveCopy();
};
}
}

#endif

