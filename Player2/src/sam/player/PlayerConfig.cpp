/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/PlayerConfig.h"

namespace sam
{   
namespace player
{    
PlayerConfig::PlayerConfig()
{
    // DB virtual board
    virtualBoardAddress = "tcp://127.0.0.1:3306"; // for mySql server
    virtualBoardDB = "samMemo";
    virtualBoardUser = "sam";
    virtualBoardPwd = "sam";
    
    // analyser
    requiredLoops2TrustStability = 2;
}

}
}