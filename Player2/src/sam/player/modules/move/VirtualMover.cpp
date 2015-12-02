/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/move/VirtualMover.h"

namespace sam 
{
namespace player
{     
log4cxx::LoggerPtr VirtualMover::logger(log4cxx::Logger::getLogger("sam.player"));

VirtualMover::VirtualMover() 
{
    pDatabase = new utilsDB::DBClient("tcp://127.0.0.1:3306", "samMemo", "sam", "sam");
}

VirtualMover::~VirtualMover()
{
    if (pDatabase != 0)
        delete (pDatabase);
}

bool VirtualMover::connectDB()
{
    pDatabase->connect();    
    // true if connection ok
    return (pDatabase->isConnected());    
}


void VirtualMover::putPiece(int row, int col, int pieceType)
{        
    LOG4CXX_INFO(logger, "mark cell (" << row << ", " << col << ")");
    
    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "VirtualMover: failed DB connection!");
        return;
    }

    // put the specified value in the proper row & field
    std::string cell = "cell" + std::to_string(col);
    updateBoard =  "update TAB_VIRTUAL_BOARD set " + cell + "=" + std::to_string(pieceType) 
                            + " where row_ID=" + std::to_string(row);
    
    pDatabase->write(updateBoard);
    pDatabase->commit();    
}


void VirtualMover::removePiece(int row, int col)
{        
    LOG4CXX_INFO(logger, "VirtualMover: clear cell (" << row << ", " << col << ")");

    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "VirtualMover: failed DB connection!");
        return;
    }

    std::string cell = "cell" + std::to_string(col);
    updateBoard =  "update TAB_VIRTUAL_BOARD set " + cell + "=" + std::to_string(0) 
                            + " where row_ID=" + std::to_string(row);
    
    pDatabase->write(updateBoard);
    pDatabase->commit();    
}

}
}