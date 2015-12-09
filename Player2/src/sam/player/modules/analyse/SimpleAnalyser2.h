#ifndef __SAM_PLAYER_SIMPLEANALYSER_H
#define __SAM_PLAYER_SIMPLEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/modules/analyse/LineAnalyser2.h"
#include "sam/player/modules/analyse/Strategy.h"

namespace sam 
{
namespace player
{    
// Very simple type of LineAnalyser. 
// attack moves: symplistic strategy (Strategy class).
// defense moves: none    
// knowledge: none
class SimpleAnalyser : public LineAnalyser
{
private:
    static log4cxx::LoggerPtr logger;
    Strategy oStrategy;         // symplistic strategy (used for selection of moves)

public:
    SimpleAnalyser();
            
private:    
    // searches the best attack move for the present board line
    virtual void checkMoves4Attack(int playMode);
    // searches the best defense move for the present board line
    virtual void checkMoves4Defense(int playMode);
    // updates the stored knowledge about the task (for smart players)
    virtual void storeKnowledge();
};

}
}
#endif
