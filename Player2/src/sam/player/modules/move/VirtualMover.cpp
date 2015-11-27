/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/modules/move/VirtualMover.h"

namespace sam 
{
namespace player
{     
log4cxx::LoggerPtr VirtualMover::logger(log4cxx::Logger::getLogger("sam.player"));

VirtualMover::VirtualMover() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    con = 0;
}

VirtualMover::~VirtualMover()
{
    oDatabase.closeConnectionDB();        
}

bool VirtualMover::connectDB()
{
    // if not connected or connection closed, reconnect
    if (con == 0 || con->isClosed())        
        con = oDatabase.getConnectionDB();
    
    // true if connection ok
    return (con != 0); 
}


void VirtualMover::putPiece(int row, int col, int pieceType)
{        
    LOG4CXX_INFO(logger, "VirtualMover: put piece " << pieceType << " in cell (" << row << ", " << col << ")");
    
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
    
    oDatabase.update(updateBoard, con);
    con->commit();
}


void VirtualMover::removePiece(int row, int col)
{        
    LOG4CXX_INFO(logger, "VirtualMover: remove piece from cell (" << row << ", " << col << ")");

    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "VirtualMover: failed DB connection!");
        return;
    }

    std::string cell = "cell" + std::to_string(col);
    updateBoard =  "update TAB_VIRTUAL_BOARD set " + cell + "=" + std::to_string(0) 
                            + " where row_ID=" + std::to_string(row);
    
    oDatabase.update(updateBoard, con);
    con->commit();
}

}
}