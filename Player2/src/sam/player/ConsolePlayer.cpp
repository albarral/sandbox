/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <bits/basic_string.h>

#include "sam/player/ConsolePlayer.h"

namespace sam 
{
namespace player
{  
log4cxx::LoggerPtr ConsolePlayer::logger(log4cxx::Logger::getLogger("sam.player"));

ConsolePlayer::ConsolePlayer() 
{
    bQuitGame = false;
    mark = 2;
}

ConsolePlayer::~ConsolePlayer() 
{
}


void ConsolePlayer::play()
{ 
    // ask selected row
    oConsole.ask("row?");    
    std::string answerRow = oConsole.getAnswer();
    // check for quit command
    if (answerRow == "q")
    {
        LOG4CXX_INFO(logger, "ConsolePlayer: quit game"); 
        bQuitGame = true;
        return;
    }
    // ask selected col
    oConsole.ask("col?");    
    std::string answerCol = oConsole.getAnswer();
    // check for quit command
    if (answerCol == "q")
    {
        LOG4CXX_INFO(logger, "ConsolePlayer: quit game"); 
        bQuitGame = true;
        return;
    }
    
    int row = std::stoi(answerRow);
    int col = std::stoi(answerCol);
    // make move if valid cell
    if (row >= 0 && row < 3 && col >= 0 && col < 3 )
    {
        oVirtualMover.putPiece(row, col, mark);
    }
    else
    {
        LOG4CXX_WARN(logger, "ConsolePlayer: invalid cell, ignored"); 
    }
}

}
}