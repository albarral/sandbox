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
        brooks::Control coWatcherInhibit; 
        brooks::Control coWatcherAck;     
        // analyser module
        brooks::Control coAnalyserInhibit;
        brooks::Control coAnalyseFull;
        
        
    public:
        COBus();
        // watcher module        
        brooks::Control& getCO_WATCHER_INHIBIT() {return coWatcherInhibit;};           
        brooks::Control& getCO_WATCHER_ACK() {return coWatcherAck;};           
        // analyser module
        brooks::Control& getCO_ANALYSER_INHIBIT() {return coAnalyserInhibit;};           
        brooks::Control& getCO_ANALYSE_FULL() {return coAnalyseFull;};           
};

}
}    
#endif
