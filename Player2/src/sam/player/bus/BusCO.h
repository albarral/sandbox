#ifndef __SAM_PLAYER_BUSCO_H
#define __SAM_PLAYER_BUSCO_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include "sam/utils/brooks/control.h"

namespace sam 
{
namespace player 
{    
// Part of the bus involving control data
class BusCO
{
    private:                
        // TMP (use Brooks controls)
        bool coLineCheck; 
        int coCheckedLine; 
//        goon::Control coLineCheck; 
//        goon::Control coCheckedLine; 
        
    public:
        BusCO();
        
        bool& getCO_LineCheck() {return coLineCheck;};        
        int& getCO_CheckedLine() {return coCheckedLine;};           
//        goon::Control& getCO_LineCheck() {return coLineCheck;};        
//        goon::Control& getCO_CheckedLine() {return coCheckedLine;};           
};

}
}    
#endif
