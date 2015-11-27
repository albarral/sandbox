#ifndef __SAM_PLAYER_BUS_H
#define __SAM_PLAYER_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <string>

#include "sam/player/bus/COBus.h"
#include "sam/player/bus/SOBus.h"


namespace sam 
{
namespace player
{    
// Bus for modules interconnection inside player app
class Bus
{
    private:        
        bool benabled;        
        COBus oCOBus;   // control data
        SOBus oSOBus;   // sensor data
                
    public:
        Bus();

        COBus& getCOBus() {return oCOBus;};
        SOBus& getSOBus() {return oSOBus;};
};

}
}    
#endif
