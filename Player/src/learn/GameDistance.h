#ifndef __SAM_GAMEDISTANCE_H
#define __SAM_GAMEDISTANCE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace sam
{      
class GameDistance 
{   
public:
    GameDistance();
    
    int static computeDistance2Victory(int mines, int others);
    int static computeDistance2Defeat(int mines, int others);
};
}

#endif

