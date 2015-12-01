#ifndef __SAM_PLAYER_BOARDZONE_H
#define __SAM_PLAYER_BOARDZONE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

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
    
    void setID(std::string value) {ID = value;};
    std::string getID() {return ID;};
    
    void setType(int value) {type = value;};
    int getType() {return type;}
    
    void setOrdinal(int value) {ordinal = value;};
    int getOrdinal() {return ordinal;}

    void setNumElements(int value) {numElements = value;};    
    int getNumElements() {return numElements;};    
};

}
}
#endif
