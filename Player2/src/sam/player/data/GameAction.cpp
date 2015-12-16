/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/GameAction.h"

namespace sam
{    
namespace player
{     
GameAction::GameAction() 
{
 }
 
void GameAction::resetAvailableMoves()
{
    std::lock_guard<std::mutex> locker(mutex1);
    listGameMoves.clear();
    //listDefenseMoves.clear();
}

void GameAction::addGameMove(GameMove& oMove)
{
    std::lock_guard<std::mutex> locker(mutex1);
    listGameMoves.push_back(oMove);
}

//void GameAction::addDefenseMove(GameMove& oMove)
//{
//    std::lock_guard<std::mutex> locker(mutex1);
//    listDefenseMoves.push_back(oMove);
//}

void GameAction::getCopyGameMoves(std::vector<GameMove>& listMoves)
{
    std::lock_guard<std::mutex> locker(mutex1);
    listMoves = listGameMoves;
}

//void GameAction::getCopyDefenseMoves(std::vector<GameMove>& listMoves)
//{
//    std::lock_guard<std::mutex> locker(mutex1);
//    listMoves = listDefenseMoves;
//}

void GameAction::updateMovementInfo(Move& fromMove, Move& toMove, GamePiece& oGamePiece)
{
    std::lock_guard<std::mutex> locker(mutex2);
    this->fromMove = fromMove;
    this->toMove = toMove;
    this->movedPiece = oGamePiece;
}

Move GameAction::getFromMoveCopy()
{
    std::lock_guard<std::mutex> locker(mutex2);
    return fromMove;
}

Move GameAction::getToMoveCopy()
{
    std::lock_guard<std::mutex> locker(mutex2);
    return toMove;
}

GamePiece GameAction::getGamePieceCopy()
{
    std::lock_guard<std::mutex> locker(mutex2);
    return movedPiece;
}

}
}