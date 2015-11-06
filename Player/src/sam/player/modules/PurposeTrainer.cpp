/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/PurposeTrainer.h"

namespace sam
{   
namespace player
{
PurposeTrainer::PurposeTrainer()
{
    playerType = PlayerPurpose::eTYPE_TRAINER;
    playMode = PlayerPurpose::eMODE_SIMPLE;
}

void PurposeTrainer::reset()
{
    gamesPlayed = 0;
}

void PurposeTrainer::evolve()
{
    gamesPlayed++;
}

bool PurposeTrainer::want2PlayMore()
 {
     // the trainer agent always wants to play
     return true;     
 }
}
}