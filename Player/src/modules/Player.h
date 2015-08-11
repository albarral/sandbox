#ifndef __SAM_PLAYER_H
#define __SAM_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp" //for the matrix

#include "utils/module2.h"

namespace sam 
{
// It derives from base class Module2
class Player : public Module2
{
public:
    // states of Player module
    enum eType
    {
         eSTATE_WAIT, 
         eSTATE_PLAY, 
         eSTATE_WINNER
    };

private:
    static log4cxx::LoggerPtr logger;
    int type;       // used navigation strategy

public:
    Player();
    
    // initializes the module 
    void init ();
    // gets type code
    int getType() {return type;};
    
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    
    void chooseCell();
    void isWinner(cv::Mat matrix);
    
    // shows the present state name
    void showState();    

};
}
#endif
