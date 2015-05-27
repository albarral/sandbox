/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "ConnectionType.h"

namespace sam
{
ConnectionType::ConnectionType() 
{
}

void ConnectionType::set(int type)
{
    switch (type)
    {
        case eTYPE_PLANO_CORTO:
            inform("plano_corto", 5, 0, 0);
            break;
        case eTYPE_PLANO_LARGO:
            inform("plano_largo", 20, 0, 0);
            break;
        case eTYPE_SUBIDA_CORTA:
            inform("subida_corta", 5, 5, 0);
            break;
        case eTYPE_SUBIDA_LARGA:
            inform("subida_larga", 20, 5, 0);
            break;
        case eTYPE_BAJADA_CORTA:
            inform("bajada_corta", 5, -5, 0);
            break;
        case eTYPE_BAJADA_LARGA:
            inform("bajada_larga", 20, -5, 0);
            break;            
        default:
            inform("unknown", 10, 1, 1);
            break;
    }
}

void ConnectionType::inform(std::string desc, int length, int slope, int abruptness)
{
    this->description = desc;
    this->length = length;
    this->slope = slope;
    this->abruptness = abruptness;
}

}