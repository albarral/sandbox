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
        brooks::SensorT<int> soWatcherState; 
        brooks::SensorT<int> soStableTime;         
        // analyser module
        brooks::SensorT<int> soAnalyserState; 
        
    public:
        SOBus();
        // watcher module        
        brooks::SensorT<int>& getSO_WATCHER_STATE(){return soWatcherState;};        
        brooks::SensorT<int>& getSO_STABLE_TIME() {return soStableTime;};           
        // analyser module
        brooks::SensorT<int>& getSO_ANALYSER_STATE(){return soAnalyserState;};        
};

}
}    
#endif
