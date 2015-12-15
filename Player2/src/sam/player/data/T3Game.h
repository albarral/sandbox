#ifndef __SAM_PLAYER_T3GAME_H
#define __SAM_PLAYER_T3GAME_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/Game.h"

namespace sam
{
namespace player
{    
// Class that represents the tic-tac-toe game
// It has 2 different GamePieces: 1 mine, 1 opponent's
// Derives from Game
class T3Game : public Game
{
public:
    // piece types
    enum ePieceTypes 
    {
        ePIECE_UNDEFINED,
        ePIECE_UNIQUE,
        ePIECE_DIM 
    };
    // teams
    enum eTeams
    {
        eTEAM_UNDEFINED,
        eTEAM_ME,
        eTEAM_OPPONENT,
        eTEAM_DIM 
    };
        
private:
    int pieces4Player;  // num pieces for each player
    
public:    
    T3Game();        
    
    // returns a list of piece types
    // virtual std::vector<int> getPieceTypes();
    // returns a list of teams
    // virtual std::vector<int> getTeams();
};

}
}
#endif
