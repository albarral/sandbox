/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include "Connection.h"

Connection::Connection() 
{
    ID = 0;
    environmentID = 0;
    placeID = 0;
    nextPlace = 0;
    length = 0;
    slope = 0;
    abruptness = 0;
}

void Connection::loadFromMemo()
{}

int Connection::getID() const
{ 
    return ID; 
}

void Connection::setID(int id)
{
    ID = id;
}    

string Connection::getDesc() const
{ 
    return desc; 
}

void Connection::setDesc(string de)
{
    desc = de;
}

int Connection::getEnvironmentID() const
{ 
    return environmentID; 
}

void Connection::setEnvironmentID(int eID)
{
    environmentID = eID;
}

int Connection::getPlaceID() const
{ 
    return placeID; 
}

void Connection::setPlaceID(int pID)
{
    placeID = pID;
}   

int Connection::getNextPlace() const
{ 
    return nextPlace; 
}

void Connection::setNextPlace(int nxPlc)
{
    nextPlace = nxPlc;
} 

int Connection::getLength() const
{ 
    return length; 
}

void Connection::setLength(int leng)
{
    length = leng;
} 

int Connection::getSlope() const
{ 
    return slope; 
}

void Connection::setSlope(int slp)
{
    slope = slp;
} 

int Connection::getAbruptness() const
{ 
    return abruptness; 
}

void Connection::setAbruptness(int abtns)
{
    abruptness = abtns;
} 