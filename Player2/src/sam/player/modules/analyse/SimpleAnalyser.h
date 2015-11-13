#ifndef __SAM_PLAYER_SIMPLEANALYSER_H
#define __SAM_PLAYER_SIMPLEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/player/modules/analyse/LineAnalyser.h"
#include "sam/player/modules/analyse/Strategy.h"

namespace sam 
{
namespace player
{    
// Very simple type of LineAnalyser. 
// Selects attack moves using a symplistic strategy (Strategy class).
// It makes no defense moves.    
// It doesn't generate knowledge.    
class SimpleAnalyser : public LineAnalyser
{
private:
    static log4cxx::LoggerPtr logger;
    Strategy oStrategy;         // symplistic strategy (used for selection of moves)

public:
    SimpleAnalyser();
            
private:    
    // searches the best attack move for the present board line
    virtual void searchBestAttack();
    // searches the best defense move for the present board line
    virtual void searchBestDefense();
    // updates the stored knowledge about the task (for smart players)
    virtual void storeKnowledge();
};

}
}
#endif
