#ifndef __SAM_PLAYER_GAME_H
#define __SAM_PLAYER_GAME_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "sam/player/utils/GamePiece.h"

namespace sam
{
namespace player
{    
// Utility base class to represent a game
class Game
{
private:   
    std::vector<GamePiece> listGamePieces;      // list of zones in the board
    
public:
    Game();
              
    int getNumPieces();
    // add new piece to the game
    void addGamePiece(GamePiece& oGamePiece);    
    // returns the list of game pieces in the game
    std::vector<GamePiece>& getListGamePieces() {return listGamePieces;};    
    // returns a list of piece types
//    virtual std::vector<int> getPieceTypes() = 0;
    // returns a list of teams
//    virtual std::vector<int> getTeams() = 0;
};

}
}
#endif
