#ifndef __SAM_PLAYER_CONSOLEPLAYER_H
#define __SAM_PLAYER_CONSOLEPLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/modules/move/VirtualMover.h"
#include "sam/utils/Console.h"

namespace sam 
{
namespace player
{  
// Class used to allow a user playing through the console.    
class ConsolePlayer
{
private:
    static log4cxx::LoggerPtr logger;
    VirtualMover oVirtualMover;
    utils::Console oConsole;
    bool bQuitGame;     // flag indicating the user wants to quit game
    int mark;               // user mark
    
public:
    ConsolePlayer();
    ~ConsolePlayer();

    void init();
    // request cell selection through the console and perform the (virtual) movement
    void play();
    // check if user wants to quit the game (responded "q")
    bool want2QuitGame() {return bQuitGame;};
};
}
}

#endif
