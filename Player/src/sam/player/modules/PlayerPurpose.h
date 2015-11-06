#ifndef __SAM_PLAYER_PURPOSE_H
#define __SAM_PLAYER_PURPOSE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam
{
namespace player
{    
// Base class used to manage the agent's purpose.
// The purpose involves 2 concepts: 
// - the will to play a new game
// - the game strategy to be used by the player (or playing mode)
// And will evolve through the time affecting both the will to play & the playing mode.
// Different player types can be defined, each with its own specific purpose (that will be implemented in its own derived class).
class PlayerPurpose
{
public:
    enum eTypes  // player type
    {
        eTYPE_TRAINER,             // trainer: uses the SIMPLE playing mode
        eTYPE_WINNER,              // winner: uses SMART & SMART_EXPLORE playing modes 
        eTYPE_UNKNOWN
    };
    
    enum eModes  // playing modes
    {
        eMODE_RANDOM,             // random player: selects cells in aleatory manner
        eMODE_SIMPLE,               // simple player: uses rules defined in Strategy class
        eMODE_SMART,                 // smart player: uses knowledge & learns
        eMODE_SMART_EXPLORE,   // smart explorative player: explores & learns
        eMODE_UNKNOWN
    };

protected:           
    int playerType;                   // player type (eTypes)
    int playMode;           // playing mode (eModes)
    int gamesPlayed;      // number of games played in the present playing round
            
public:
    PlayerPurpose();
    
    // resets purpose
    virtual void reset() = 0;
    // evolves purpose
    virtual void evolve() = 0;
    // checks if agent wants to play a new game
    virtual bool want2PlayMore() = 0;

    void setPlayerType(int value) {playerType = value;};    
    int getPlayerType() {return playerType;};
    void setPlayMode(int value) {playMode = value;};    
    int getPlayMode() {return playMode;};
    int getGamesPlayed() {return gamesPlayed;};        

    bool isSimplePlayer() {return (playMode == eMODE_SIMPLE);};
    bool isSmartPlayer() {return (playMode == eMODE_SMART);};
    bool isExplorativePlayer() {return (playMode == eMODE_SMART_EXPLORE);};
};

}
}
#endif
