#ifndef __SAM_PLAYER_BOARDZONE_H
#define __SAM_PLAYER_BOARDZONE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

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
    int ID;
    int type;
    int numElements;
    
public:
    BoardZone();

    virtual std::vector<int> getZoneTypes();
    
    void setID(int value) {ID = value;};
    int getID() {return ID;};
    
    void setType(int value) {type = value;};
    int getType() {return type;}
    
    void setNumElements(int value) {numElements = value;};    
    int getNumElements() {return numElements;};    
};

}
}
#endif
