#ifndef __SAM_PLAYER_PLAYERCONFIG_H
#define __SAM_PLAYER_PLAYERCONFIG_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
namespace player
{    
// This class holds configuration parameters for player modules.
class PlayerConfig
{
private:     
    // DB virtual board
    std::string virtualBoardAddress; // address of DB virtual board  
    std::string virtualBoardDB;     // schema of DB virtual board
    std::string virtualBoardUser;  // user for DB virtual board
    std::string virtualBoardPwd;  // password for DB virtual board
    // analyser
    int requiredLoops2TrustStability;      // minimum required time to trust board stability
            
public:
    PlayerConfig();
    
    std::string getVirtualBoardAddress() {return virtualBoardAddress;};
    std::string getVirtualBoardDB() {return virtualBoardDB;};
    std::string getVirtualBoardUser() {return virtualBoardUser;};
    std::string getVirtualBoardPwd() {return virtualBoardPwd;};
    int getRequiredLoops2TrustStability() {return requiredLoops2TrustStability;};
};

}
}

#endif
