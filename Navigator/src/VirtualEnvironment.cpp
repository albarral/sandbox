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
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    oEnvironment.setDatabase(oDatabase);
    placeNow = 0;        
}

void VirtualEnvironment::build6RoomTest()
{
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5;
    Connection oConnection;
    oEnvironment.setID(1);
    
    std::cout << "6 room environment" <<std::endl;

    oPlace0.setID(0);  
    oPlace0.setEnvironmentID(1);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(1);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(1);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(1);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(1);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(1);
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(1);
    oConnection.setLength(5);
    oConnection.setSlope(0);
    oConnection.setAbruptness(0);
    
    // 0 -> 4
    oConnection.setPlaceID(0);
    oConnection.setNextPlace(4);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(3);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.setNextPlace(5);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(3);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(1);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.setNextPlace(4);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(0);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.setNextPlace(3);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 5
    oConnection.setNextPlace(5);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 4    
    oConnection.setNextPlace(4);
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
    
    std::cout << "environment built" << std::endl << std::endl;       
}

void VirtualEnvironment::build7RoomTest()
{
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5, oPlace6;
    Connection oConnection;
    oEnvironment.setID(2);
    
    std::cout << "7 room environment" <<std::endl;

    oPlace0.setID(0);  
    oPlace0.setEnvironmentID(2);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(2);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(2);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(2);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(2);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(2);
    oPlace6.setID(6);
    oPlace6.setEnvironmentID(2);
    
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(2);
    oConnection.setLength(5);
    oConnection.setSlope(0);
    oConnection.setAbruptness(0);
    
    // 0 -> 4
    oConnection.setPlaceID(0);
    oConnection.setNextPlace(4);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(3);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.setNextPlace(5);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(3);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(1);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.setNextPlace(4);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(0);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.setNextPlace(3);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 6
    oConnection.setNextPlace(6);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 6    
    oConnection.setNextPlace(6);
    oPlace5.addConnection(oConnection);
    
    // 6 -> 4
    oConnection.setPlaceID(6);
    oConnection.setNextPlace(4);
    oPlace6.addConnection(oConnection);
    
    // 6 -> 5    
    oConnection.setNextPlace(5);
    oPlace6.addConnection(oConnection);
    
    oPlace0.showData();
    oPlace1.showData();
    oPlace2.showData();
    oPlace3.showData();
    oPlace4.showData();
    oPlace5.showData();
    oPlace6.showData();
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    oEnvironment.addPlace(oPlace6);
  
    std::cout << "environment built" << std::endl << std::endl;       
}

void VirtualEnvironment::build8RoomTest()
{
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5, oPlace6, oPlace7;
    Connection oConnection;
    oEnvironment.setID(3);
    
    std::cout << "8 room environment" <<std::endl;

    oPlace0.setID(0);  
    oPlace0.setEnvironmentID(3);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(3);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(3);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(3);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(3);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(3);
    oPlace6.setID(6);
    oPlace6.setEnvironmentID(3);
    oPlace7.setID(7);
    oPlace7.setEnvironmentID(3);
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(3);
    oConnection.setLength(5);
    oConnection.setSlope(0);
    oConnection.setAbruptness(0);
    
    // 0 -> 4
    oConnection.setPlaceID(0);
    oConnection.setNextPlace(4);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(3);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.setNextPlace(5);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(3);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(1);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.setNextPlace(4);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(0);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.setNextPlace(3);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 6
    oConnection.setNextPlace(6);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 7    
    oConnection.setNextPlace(7);
    oPlace5.addConnection(oConnection);
    
    // 6 -> 4
    oConnection.setPlaceID(6);
    oConnection.setNextPlace(4);
    oPlace6.addConnection(oConnection);
    
    // 6 -> 7   
    oConnection.setNextPlace(7);
    oPlace6.addConnection(oConnection);
    
    // 7 -> 5
    oConnection.setPlaceID(7);
    oConnection.setNextPlace(5);
    oPlace7.addConnection(oConnection);
    
    // 7 -> 6   
    oConnection.setNextPlace(6);
    oPlace7.addConnection(oConnection);
    
    oPlace0.showData();
    oPlace1.showData();
    oPlace2.showData();
    oPlace3.showData();
    oPlace4.showData();
    oPlace5.showData();
    oPlace6.showData();
    oPlace7.showData();
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    oEnvironment.addPlace(oPlace6);
    oEnvironment.addPlace(oPlace7);
  
    std::cout << "environment built" << std::endl << std::endl;       
}

void VirtualEnvironment::init(int ID)
{
    oEnvironment.setID(ID);
    
    loadFromMemo();
    
    if(oEnvironment.getListPlaces().size() <= 0)
    {
        create();
    }      
}

void VirtualEnvironment::create()
{
    if(oEnvironment.getID() == 1)
    {
        build6RoomTest();
    }
    
    else if(oEnvironment.getID() == 2)
    {
        build7RoomTest();
    }
    
    else if(oEnvironment.getID() == 3)
    {
        build8RoomTest();
    }
    
    else{}
    
    storeInMemo();
}

void VirtualEnvironment::storeInMemo()
{    
    oEnvironment.storeInMemo();
    
//    oEnvironment.storeInMemo();
//    oEnvironment.deleteFromMemo();
//    oConnection.deleteFromMemo();
//    oPlace2.deleteFromMemo();
//    oPlace5.upDateInMemo();    
}

void VirtualEnvironment::loadFromMemo()
{    
    oEnvironment.loadFromMemo();
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