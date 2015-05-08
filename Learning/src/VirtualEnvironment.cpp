/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualEnvironment.h"

namespace sam 
{
VirtualEnvironment::VirtualEnvironment() 
{
    placeNow = 0;
}

void VirtualEnvironment::build6RoomTest()
{
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5;
    Connection oConnection;
    oEnvironment.setID(1);
    
    std::cout << "6 room environment" <<std::endl;

    oPlace0.setID(1);    
    oPlace1.setID(2);    
    oPlace2.setID(3);
    oPlace3.setID(4);    
    oPlace4.setID(5);    
    oPlace5.setID(6);
   
    // default connection properties for an office environment
    oConnection.setLength(5);
    oConnection.setSlope(0);
    oConnection.setAbruptness(0);
    
    // 0 -> 4
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(5);
    oPlace0.addConnection(oConnection);
    
    // 1 -> 3
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(4);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.setNextPlace(6);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(4);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);    
    
    // 3 -> 2
    oConnection.setNextPlace(3);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.setNextPlace(5);
    oPlace3.addConnection(oConnection);
    
    // 4 -> 0
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.setNextPlace(4);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 5
    oConnection.setNextPlace(6);
    oPlace4.addConnection(oConnection);
    
    // 5 -> 1
    oConnection.setPlaceID(6);
    oConnection.setNextPlace(2);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 4    
    oConnection.setNextPlace(5);
    oPlace5.addConnection(oConnection);
    
    oPlace0.showData();
    oPlace1.showData();
    oPlace2.showData();
    oPlace3.showData();
    oPlace4.showData();
    oPlace5.showData();
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    
    oEnvironment.storeInMemo();

    std::cout << "environment built" << std::endl << std::endl;       
}

std::vector<Connection>& VirtualEnvironment::getPresentConnections()
{
    int connectionID;

    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    return mPlaceNow.getListConnections();
}


void VirtualEnvironment::crossConnection(int connectionID)
{
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    Connection& mConnection = mPlaceNow.getListConnections().at(connectionID);
    setPlaceNow(mConnection.getNextPlace());
}

int VirtualEnvironment::getPlaceNow() const
{ 
    return placeNow; 
}

void VirtualEnvironment::setPlaceNow(int pNow)
{
    placeNow = pNow;
}    

}