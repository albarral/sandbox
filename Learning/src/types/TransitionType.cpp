/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "TransitionType.h"

namespace sam
{
TransitionType::TransitionType() 
{
}

void TransitionType::set(int type)
{
    switch (type)
    {
        case eTYPE_PLANO_CORTO:
            inform("plano_corto", 5);
            break;
        case eTYPE_PLANO_LARGO:
            inform("plano_largo", 10);
            break;
        case eTYPE_SUBIDA_CORTA:
            inform("subida_corta", 10);
            break;
        case eTYPE_SUBIDA_LARGA:
            inform("subida_larga", 20);
            break;
        case eTYPE_BAJADA_CORTA:
            inform("bajada_corta", 5);
            break;
        case eTYPE_BAJADA_LARGA:
            inform("bajada_larga", 10);
            break;            
        default:
            inform("unknown", 10);
            break;
    }
}

void TransitionType::inform(std::string desc, float cost)
{
    this->description = desc;
    this->cost = cost;
}

}