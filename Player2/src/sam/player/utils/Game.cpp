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

}
}