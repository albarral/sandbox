#ifndef __SAM_PLAYER_GAMEPIECE_H
#define __SAM_PLAYER_GAMEPIECE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
namespace player
{    
// Utility class to represent a game piece
class GamePiece
{
protected:   
    std::string ID;
    int type;
    int team;
    int numInstances;
    
public:
    GamePiece();
    
    std::string getID() {return ID;};
    void setID(std::string value) {ID = value;};
    
    int getType() {return type;}
    void setType(int value) {type = value;};
    
    int getTeam() {return team;}
    void setTeam(int value) {team = value;};

    int getNumInstances() {return numInstances;};    
    void setNumInstances(int value) {numInstances = value;};    
    
    // gets description
    std::string toString();

};

}
}
#endif
