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
        brooks::Control CO_WATCHER_INHIBIT; 
        brooks::Control CO_WATCHER_ACK;     
        // analyser module
        brooks::Control CO_ANALYSER_INHIBIT;
        brooks::Control CO_ANALYSER_FULLCHECK;
        brooks::Control CO_ANALYSER_NEWPLAYMODE;
        
    public:
        COBus();
        // watcher module        
        brooks::Control& getCO_WATCHER_INHIBIT() {return CO_WATCHER_INHIBIT;};           
        brooks::Control& getCO_WATCHER_ACK() {return CO_WATCHER_ACK;};           
        // analyser module
        brooks::Control& getCO_ANALYSER_INHIBIT() {return CO_ANALYSER_INHIBIT;};           
        brooks::Control& getCO_ANALYSER_FULLCHECK() {return CO_ANALYSER_FULLCHECK;};           
        brooks::Control& getCO_ANALYSER_NEWPLAYMODE() {return CO_ANALYSER_NEWPLAYMODE;};
};

}
}    
#endif
