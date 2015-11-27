#ifndef __SAM_PLAYER_BUSCO_H
#define __SAM_PLAYER_BUSCO_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/control.h"

namespace sam 
{
namespace player 
{    
// Control part of the bus
class COBus
{
    private:                
        // watcher module
        brooks::Control coInhibitWatcher; 
        brooks::Control coResetWatcher; 
        
    public:
        COBus();
        
        brooks::Control& getCO_INHIBIT_WATCHER() {return coInhibitWatcher;};           
        brooks::Control& getCO_RESET_WATCHER() {return coResetWatcher;};           
};

}
}    
#endif
