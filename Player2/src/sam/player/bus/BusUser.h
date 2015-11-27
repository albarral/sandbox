#ifndef __SAM_PLAYER_BUSUSER_H
#define __SAM_PLAYER_BUSUSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/bus/Bus.h"

namespace sam 
{
namespace player
{        
// Base class representing a user of the player bus.
// Intended to be derived by player modules in conjunction with the Module class.
class BusUser 
{
protected:
    bool bconnected;        // connected to bus
    Bus* pBus;

public:
        BusUser();
        //~BusUser();
                
       // bus connection 
       void connect(Bus& oBus);
       bool isConnected() {return bconnected;};
};

}
}
#endif
