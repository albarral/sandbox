#ifndef __SAM_PLAYER_GAMEACTION_H
#define __SAM_PLAYER_GAMEACTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

#include "sam/player/utils/GameMove.h"
#include "sam/player/utils/GamePiece.h"
#include "sam/player/utils/Move.h"

namespace sam
{  
namespace player
{     
// (shared data) This class is used to represent the next game action.
// It holds a list of available game moves (attack & defense).
// And also the selected final movement (from Move, to Move & game piece)
// mutex protected
class GameAction 
{  
private:
    std::mutex mutex1;  // for game moves
    std::mutex mutex2;  // for final movement
    // available game moves ...
    std::vector<GameMove> listGameMoves;         // for attack&defense
    //std::vector<GameMove> listDefenseMoves;      // for defense
    // final movement ...
    Move fromMove;                   // picking move               
    Move toMove;                       // placing move         
    GamePiece movedPiece;      // moved piece 
    
public:
    GameAction();
    
    // reset available moves
    void resetAvailableMoves();
    // increase the list of available game moves        
    void addGameMove(GameMove& oMove);
    //void addDefenseMove(GameMove& oMove);
    // get copy of available game moves        
    void getCopyGameMoves(std::vector<GameMove>& listMoves);
    //void getCopyDefenseMoves(std::vector<GameMove>& listMoves);
    
    void updateMovementInfo(Move& fromMove, Move& toMove, GamePiece& oGamePiece);
    Move getFromMoveCopy();
    Move getToMoveCopy();
    GamePiece getGamePieceCopy();
};
}
}

#endif

