/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "sam/player/data/T3Game.h"
#include "sam/player/utils/GamePiece.h"

namespace sam
{   
namespace player
{
T3Game::T3Game()
{
    // define the list of pieces of the tic-tac-toe game
    pieces4Player = 5;
    std::string pieceID; // the zone ID 
    
    // my piece
    GamePiece oMyPiece;
    pieceID = "mine";
    oMyPiece.setType(T3Game::ePIECE_UNIQUE);    
    oMyPiece.setTeam(T3Game::eTEAM_ME);
    oMyPiece.setNumInstances(pieces4Player);
    for (int i=0; i<pieces4Player; i++)
    {
        addGamePiece(oMyPiece);                
    }
    
    // add the 3 columns 
    GamePiece oRivalPiece;
    pieceID = "rival";
    oRivalPiece.setType(T3Game::ePIECE_UNIQUE);    
    oRivalPiece.setTeam(T3Game::eTEAM_OPPONENT);
    oRivalPiece.setNumInstances(pieces4Player);
    for (int i=0; i<pieces4Player; i++)
    {
        addGamePiece(oRivalPiece);                
    }            
}

}
}