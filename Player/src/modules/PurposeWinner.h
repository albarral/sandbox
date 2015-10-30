#ifndef __SAM_PLAYER_WINNERPURPOSE_H
#define __SAM_PLAYER_WINNERPURPOSE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "modules/PlayerPurpose.h"

namespace sam
{
// Class that manages the purpose of a WINNER player type.
// The winner player starts playing in EXPLORATIVE mode. This is done to acquire a good knowledge base.
// Then changes to SMART playing mode. This is done to make use of its acquired knowledge.
// Parameters:
// - games2Play: the will to play finishes when gamesPlayed reaches this value. 
// - games2Learn: the playing mode changes when gamesPlayed reaches this value.
class PurposeWinner : public PlayerPurpose
{
private:           
    int games2Learn;   // number of games used for explorative mode
    int games2Play;     // number of games the agent wants to play
            
public:
    PurposeWinner();
    
    // resets purpose
    virtual void reset();
    // evolves purpose
    virtual void evolve();
    // checks if agent wants to play a new game
    virtual bool want2PlayMore();

    void setGames2Learn(int value) {games2Learn = value;};    
    int getGames2Learn() {return games2Learn;};

    void setGames2Play(int value) {games2Play = value;};    
    int getGames2Play() {return games2Play;};
};

}

#endif
