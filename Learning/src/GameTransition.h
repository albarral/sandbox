#ifndef __SAM_GAMETRANSITION_H
#define __SAM_GAMETRANSITION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "Transition.h"

namespace sam 
{
class GameTransition : public Transition
{
private:
    float QAttack;
    float QDefend;
  
public:
    GameTransition();
    
    float getQAttack() {return QAttack;};
    void setQAttack(float value) {QAttack = value;};
    
    float getQDefend() {return QDefend;};
    void setQDefend(float value) {QDefend = value;};

};
}

#endif
