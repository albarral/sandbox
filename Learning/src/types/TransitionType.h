#ifndef __SAM_TRANSITION_TYPE_H
#define __SAM_TRANSITION_TYPE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
// Class to handle the different transition types among states    
class TransitionType
{
public:
    enum eTypes
    {
        eTYPE_PLANO_CORTO,
        eTYPE_PLANO_LARGO,
        eTYPE_SUBIDA_CORTA,
        eTYPE_SUBIDA_LARGA,
        eTYPE_BAJADA_CORTA,
        eTYPE_BAJADA_LARGA,
        eTYPE_UNKNOWN
    };
        
private:
    int type;
    float cost;
    std::string description;
    
public:
    TransitionType();
    
    // sets the connection values depending on its type
    void set(int type);
    
    int getType() {return type;};
    float getCost() {return cost;};   
    std::string& getDesc() {return description;};
    
private:
    void inform(std::string desc, float cost);
};
}

#endif
