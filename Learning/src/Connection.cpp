/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "Connection.h"

namespace sam
{
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

std::string Connection::getDesc() const
{ 
    return desc; 
}

void Connection::setDesc(std::string de)
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

// computes the cost of traversing the connection
float Connection::computeCost()
{
    return (length * slope * abruptness);
}

void Connection::showData()
{
    std::cout << "connection " << ID << ": " << placeID << " -> " << nextPlace << std::endl;

}

}