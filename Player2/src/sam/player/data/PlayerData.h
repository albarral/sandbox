#ifndef __SAM_PLAYER_PLAYERDATA_H
#define __SAM_PLAYER_PLAYERDATA_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <string>

namespace sam
{
namespace player
{    
// (shared data) This class represents the player data.
// It holds personal info for the player agent: it's mark, the empty mark, the playing mode (simple, smart, random ...)
class PlayerData
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
    std::mutex mutex;
    int playMode;      // playing mode used by player 
    int myMark;        // (not mutex protected) mark used by player to select cells 
    int emptyMark;    // (not mutex protected) value hold by empty cells 
            
public:
    PlayerData();
    
    // not mutex protected (not a changing variable)
    void setMyMark(int mark) {myMark = mark;};    
    int getMyMark() {return myMark;}

    // not mutex protected (not a changing variable)
    void setEmptyMark(int mark) {emptyMark = mark;};    
    int getEmptyMark() {return emptyMark;}

    void setPlayMode(int playMode);    
    int getPlayMode();
    
    bool isRandomPlayMode();
    bool isSimplePlayMode();
    bool isSmartPlayMode();
    bool isSmartExplorativePlayMode();

    // gets play mode name
    static std::string getPlayModeName(int playMode);
    // returns member values in string form
    std::string toString();    
};

}
}

#endif
