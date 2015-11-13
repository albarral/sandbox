#ifndef __SAM_PLAYER_BUS_H
#define __SAM_PLAYER_BUS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <string>

#include "sam/player/bus/BusCO.h"
#include "sam/player/bus/BusSO.h"


namespace sam 
{
namespace player
{    
// Bus for modules interconnection inside player app
class Bus
{
    private:        
        bool benabled;        
        BusCO oBusCO;   // control data
        BusSO oBusSO;   // sensor data
                
    public:
        Bus();

        BusCO& getBusCO() {return oBusCO;};
        BusSO& getBusSO() {return oBusSO;};
};

}
}    
#endif
