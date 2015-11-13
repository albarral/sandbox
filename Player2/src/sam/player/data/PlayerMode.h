#ifndef __SAM_PLAYER_PLAYERMODE_H
#define __SAM_PLAYER_PLAYERMODE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
namespace player
{    
// This class represents the player mode .
// It's where the playing mode is defined (simple, smart ...) for the agent.
class PlayerMode
{
public:
    enum eModes  // playing modes
    {
        eMODE_RANDOM,             // random player: selects cells in aleatory manner
        eMODE_SIMPLE,               // simple player: uses rules defined in Strategy class
        eMODE_SMART,                 // smart player: uses learning & knowledge
        eMODE_SMART_EXPLORE,    // smart explorative player: uses learning & knowledge
        eMODE_DIM
    };

private:           
    int playMode;      // playing mode used by player 
    int myMark;        // mark used by player to select cells
    int emptyMark;    // value hold by empty cells  
            
public:
    PlayerMode();
    
    void setMyMark(int mark) {myMark = mark;};    
    int getMyMark() {return myMark;}

    void setEmptyMark(int mark) {emptyMark = mark;};    
    int getEmptyMark() {return emptyMark;}

    void setPlayMode(int playMode);    
    int getPlayMode() {return playMode;};
    
    bool isSimplePlayer() {return (playMode == eMODE_SIMPLE);};
    bool isSmartPlayer() {return (playMode == eMODE_SMART || playMode == eMODE_SMART_EXPLORE);};
    bool isSmartExplorativePlayer() {return (playMode == eMODE_SMART_EXPLORE);};

    // returns member values in string form
    std::string toString();    
};

}
}

#endif
