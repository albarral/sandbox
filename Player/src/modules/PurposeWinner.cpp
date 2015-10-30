/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "modules/PurposeWinner.h"

namespace sam
{   
PurposeWinner::PurposeWinner()
{
    playerType = PlayerPurpose::eTYPE_WINNER;
    games2Learn = 5;    // default
    games2Play = 10;    // default
}

void PurposeWinner::reset()
{
    gamesPlayed = 0;
    playMode = PlayerPurpose::eMODE_SMART_EXPLORE;
}

void PurposeWinner::evolve()
{
    gamesPlayed++;
    // change playing mode when gamesPlayed reaches games2Learn value
    if (gamesPlayed == games2Learn)
        playMode = PlayerPurpose::eMODE_SMART;    
}

bool PurposeWinner::want2PlayMore()
 {
     // agent wants to play until the games2Play value is reached
     return (gamesPlayed < games2Play);     
 }
}
