/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/utils/Game.h"

namespace sam
{   
namespace player
{
Game::Game()
{
}

int Game::getNumPieces()
{
    return listGamePieces.size();
}

void Game::addGamePiece(GamePiece& oGamePiece)
{
    listGamePieces.push_back(oGamePiece);
}

// returns a list of pieces of the specified type
std::vector<GamePiece> Game::getPiecesOfType(int type)
{
    std::vector<GamePiece> listSpecificPieces;
    
    // walk zones list and extract those of the specified type
    for (GamePiece& oGamePiece: listGamePieces) 
    {
        if (oGamePiece.getType() == type)
            listSpecificPieces.push_back(oGamePiece);
    }

    return listSpecificPieces;
}

}
}