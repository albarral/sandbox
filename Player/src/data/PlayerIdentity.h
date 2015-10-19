#ifndef __SAM_PLAYER_PLAYERIDENTITY_H
#define __SAM_PLAYER_PLAYERIDENTITY_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
// This class represents a player's identity.
// It's also where the playing mode is defined (simple, smart ...) for the agent.
class PlayerIdentity
{
public:
    enum eModes  // playing modes
    {
        eMODE_RANDOM,             // random player: selects cells in aleatory manner
        eMODE_SIMPLE,               // simple player: uses rules defined in Strategy class
        eMODE_SMART                 // smart player: uses learning & knowledge
    };

private:           
    std::string ID;     // ID of the player 
    int myMark;        // mark used by player to select cells (can't be GameBoard::EMPTY_MARK)
    int playMode;      // playing mode used by player 
    bool bExplorationMode; 
            
public:
    PlayerIdentity();
    
    void setID(std::string ID) {this->ID = ID;};
    std::string getID() {return ID;};

    void setMyMark(int mark) {this->myMark = mark;};    
    int getMyMark() {return myMark;}

    void setPlayMode(int playMode);    
    int getPlayMode() {return playMode;};
    
    bool isSmartPlayer() {return (playMode == eMODE_SMART);};
    bool isSimplePlayer() {return (playMode == eMODE_SIMPLE);};
    bool isExplorationMode() {return (bExplorationMode == true);};
    
    // returns member values in string form
    std::string toString();
};

}

#endif
