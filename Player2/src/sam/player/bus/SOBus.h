#ifndef __SAM_PLAYER_BUSSO_H
#define __SAM_PLAYER_BUSSO_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/brooks/sensorT.h"

namespace sam 
{
namespace player 
{    
// Part of the bus involving sensor data    
class SOBus
{
    private:        
        // watcher module
        brooks::SensorT<int> SO_WATCHER_STATE; 
        brooks::SensorT<int> SO_WATCHER_STABLETIME;         
        // analyser module
        brooks::SensorT<int> SO_ANALYSER_STATE; 
        
    public:
        SOBus();
        // watcher module        
        brooks::SensorT<int>& getSO_WATCHER_STATE(){return SO_WATCHER_STATE;};        
        brooks::SensorT<int>& getSO_WATCHER_STABLETIME() {return SO_WATCHER_STABLETIME;};           
        // analyser module
        brooks::SensorT<int>& getSO_ANALYSER_STATE(){return SO_ANALYSER_STATE;};        
};

}
}    
#endif
