/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/bus/BusUser.h"

namespace sam 
{  
namespace player
{
BusUser::BusUser()
{
    bconnected = false;
    pBus = 0;
}

void BusUser::connect(Bus& oBus)
{
    pBus = &oBus;
    bconnected = true;
}

}
}