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
    enum eState
    {
        ePLAYER_OFF,			// initial state before game starts
	ePLAYER_WAIT,			// waiting for my turn
	ePLAYER_PLAY,			// it's my turn, do my move
	ePLAYER_FINISHED		// game is finished
    };

private:
    static log4cxx::LoggerPtr logger;
    int state;       // used navigation strategy
    std::string ID;

public:
    Player();
    
    // initializes the module 
    void init ();
    // gets type code
    int getState() {return state;};
    
    std::string getID() {return ID;};
    void setID(std::string value) {ID = value;};
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    
    //Put in the matrix the cell selected by the player
    void chooseCell();
    //check if there is a winner or the game is finished
    bool checkBoard(cv::Mat matrix);
    
    // shows the present state name
    void showState();    

};
}
#endif
