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
 
void GameAction::updateAttackInfo(GameMove& oMove)
{
    std::lock_guard<std::mutex> locker(mutex);
    oAttackMove = oMove;
}

void GameAction::updateDefenseInfo(GameMove& oMove)
{
    std::lock_guard<std::mutex> locker(mutex);
    oDefenseMove = oMove;
}

GameMove GameAction::getAttackMoveCopy()
{
    std::lock_guard<std::mutex> locker(mutex);
    return oAttackMove;
}

GameMove GameAction::getDefenseMoveCopy()
{
    std::lock_guard<std::mutex> locker(mutex);
    return oDefenseMove;
}

}
}