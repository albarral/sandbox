/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp" //for the matrix

#include "sam/player/modules/watch/VirtualWatcher.h"
#include "sam/player/PlayerConfig.h"

namespace sam 
{
namespace player
{    
VirtualWatcher::VirtualWatcher() 
{
    // read configuration
    PlayerConfig oPlayerConfig;
    
    oDatabase.init(oPlayerConfig.getVirtualBoardAddress(),
            oPlayerConfig.getVirtualBoardUser(),
            oPlayerConfig.getVirtualBoardPwd(), 
            oPlayerConfig.getVirtualBoardDB());
    
    con = 0;
    selectBoard = "select * from TAB_VIRTUAL_BOARD";
}

VirtualWatcher::~VirtualWatcher()
{
    oDatabase.closeConnectionDB();        
}

bool VirtualWatcher::connectDB()
{
    // if not connected or connection closed, reconnect
    if (con == 0 || con->isClosed())        
        con = oDatabase.getConnectionDB();
    
    // true if connection ok
    return (con != 0); 
}

bool VirtualWatcher::senseBoard()
{  
    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "board not sensed!");
        return false;
    }

    sql::ResultSet* res = oDatabase.select(selectBoard, con);
      
    // we must get 3 result sets, one for each row
    cv::Mat matRow;
    while (res->next())
    {       
        int i = res->getInt("row_ID");
                
        // update proper row in matrix
        matRow = matrixSensed.row(i);
        matRow.at<uchar>(0) = (uchar)res->getInt("Cell0");
        matRow.at<uchar>(1) = (uchar)res->getInt("Cell1");
        matRow.at<uchar>(2) = (uchar)res->getInt("Cell2");
    }
    return true;
}

bool VirtualWatcher::searchBoard()
{
    // try reconnection
    if (connectDB())
    {
        LOG4CXX_INFO(logger, "board found!");
        return true;
    }
    else 
    {
        LOG4CXX_ERROR(logger, "board not found!");
        return false;
    }        
}

}
}