#ifndef __SAM_CONNECTION_TYPE_H
#define __SAM_CONNECTION_TYPE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam
{
// Class to handle the different connection types among places    
class ConnectionType
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
    int length;
    int slope;
    int abruptness;
    std::string description;
    
public:
    ConnectionType();
    
    // sets the connection values depending on its type
    void set(int type);
    
    int getType() {return type;};
    int getLength() {return length;};
    int getSlope() {return slope;};   
    int getAbruptness() {return abruptness;};
    std::string& getDesc() {return description;};
    
private:
    void inform(std::string desc, int length, int slope, int abruptness);
};
}

#endif
