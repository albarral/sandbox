/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/PlayerData.h"

namespace sam
{   
namespace player
{    
PlayerData::PlayerData()
{
    myMark = -1;
    emptyMark = 0;
    setPlayMode(PlayerData::eMODE_SIMPLE);
}

void PlayerData::setPlayMode(int playMode)
{
    std::lock_guard<std::mutex> locker(mutex);
    // just set if valid value
    if (playMode >= 0 && playMode < eMODE_DIM)
        this->playMode = playMode;
}

int PlayerData::getPlayMode() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return playMode;
};

bool PlayerData::isRandomPlayMode() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return (playMode == PlayerData::eMODE_SIMPLE);
};

bool PlayerData::isSimplePlayMode() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return (playMode == PlayerData::eMODE_SIMPLE);
};

bool PlayerData::isSmartPlayMode() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return (playMode == PlayerData::eMODE_SMART || playMode == PlayerData::eMODE_SMART_EXPLORE);
};

bool PlayerData::isSmartExplorativePlayMode() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return (playMode == PlayerData::eMODE_SMART_EXPLORE);
};


std::string PlayerData::toString()
{
  return ("PlayerMode: [playMode = " + std::to_string(playMode) +  
          ", myMark = " + std::to_string(myMark) + 
          ", emptyMark = " + std::to_string(emptyMark) + "]");  
}

}
}