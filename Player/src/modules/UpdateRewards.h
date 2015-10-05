#ifndef __SAM_UPDATEREWARDS_H
#define __SAM_UPDATEREWARDS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp" // for the cv matrix

namespace sam
{  
class UpdateRewards
{   
public:
    UpdateRewards();
    
    int computeDistances();
};
}

#endif

