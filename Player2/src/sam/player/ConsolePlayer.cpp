/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include <string>
#include <stdexcept>    

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

void ConsolePlayer::init()
{
    log4cxx::NDC::push("ConsolePlayer");   	    
}

void ConsolePlayer::play()
{ 
    int row, col;    

    // ask selected cell
    oConsole.ask("select cell (x-y) ...");    
    std::string input= oConsole.getAnswer();

    // chek response and skip if wrong input
    try
    {
        // get first character
        std::string inputRow = input.substr(0,1);  
    
        // check for quit command
        if (inputRow == "q")
        {
            LOG4CXX_WARN(logger, "quit requested."); 
            bQuitGame = true;
            return;
        }

        // get third character
        std::string inputCol = input.substr(2,1);  
        // convert user input to row and column digits
        row = std::stoi(inputRow);
        col = std::stoi(inputCol);
    }
    catch (const std::exception& ex)
    {
        LOG4CXX_ERROR(logger, "Invalid response (wrong format) " << ex.what());
        return;
    }
    
    // make move if valid cell
    if (row >= 0 && row < 3 && col >= 0 && col < 3 )
    {
        oVirtualMover.putPiece(row, col, mark);
    }
    else
    {
        LOG4CXX_WARN(logger, "Invalid cell (out of board)"); 
    }    
}

}
}