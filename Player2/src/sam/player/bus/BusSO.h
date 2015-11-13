#ifndef __SAM_PLAYER_BUSSO_H
#define __SAM_PLAYER_BUSSO_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include "sam/utils/brooks/control.h"

namespace sam 
{
namespace player 
{    
// Part of the bus involving sensor data    
class BusSO
{
    private:        
        
        // TMP (use Brooks controls)
        int soLineState; 
        
    public:
        BusSO();
        
        // sensorscontrols
        int& getSO_LineState() {return soLineState;};        
};

}
}    
#endif
