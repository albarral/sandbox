#ifndef __SAM_PLAYER_BOARDZONE_H
#define __SAM_PLAYER_BOARDZONE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
namespace player
{    
// Utility base class to represent a board zone (ie. a line in a tic-tac-toe board)
// Used in Board class    
class BoardZone
{
protected:   
    std::string ID;
    int type;
    int ordinal;
    int numElements;
    
public:
    BoardZone();
    
    std::string getID() {return ID;};
    void setID(std::string value) {ID = value;};
    
    int getType() {return type;}
    void setType(int value) {type = value;};
    
    int getOrdinal() {return ordinal;}
    void setOrdinal(int value) {ordinal = value;};

    int getNumElements() {return numElements;};    
    void setNumElements(int value) {numElements = value;};    
    
    // gets description
    std::string toString();

};

}
}
#endif