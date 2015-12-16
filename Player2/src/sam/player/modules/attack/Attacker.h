#ifndef __SAM_PLAYER_ATTACKER_H
#define __SAM_PLAYER_ATTACKER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "sam/utils/Module.h"
#include "sam/player/bus/BusUser.h"
#include "sam/player/data/GameAction.h"
#include "sam/player/data/PlayerData.h"
#include "sam/player/utils/GameMove.h"

namespace sam 
{
namespace player
{    
class Attacker : public utils::Module, public BusUser
{
public:
    // states of Attacker module
    enum eState
    {
        eSTATE_SELECT,                
        eSTATE_MOVE,          
        eSTATE_DONE               
    };

protected:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    // shared data
    GameAction* pGameAction;      // next move  
    PlayerData* pPlayerData;         // marks and play mode
    // logic
    // controls & sensors
    bool binhibited;                    // module inhibition

public:
    Attacker();
    ~Attacker();
            
    // initializes the module 
    void init(GameAction& oGameAction, PlayerData& oPlayerData);
       
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    
    // updates game action with best moves
    void updateGameAction();

    // traces the changes in state
    void showStateName();     
};

}
}
#endif
