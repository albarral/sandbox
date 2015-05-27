/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualEnvironment.h"
#include "types/ConnectionType.h"

namespace sam 
{
VirtualEnvironment::VirtualEnvironment() 
{
    oDatabase.init("tcp://127.0.0.1:3306", "sam", "sam", "samMemo");
    oEnvironment.setDatabase(oDatabase);
    placeNow = 0;        
}

void VirtualEnvironment::init(int ID)
{
    oEnvironment.reset();
    oEnvironment.setID(ID);
    
    loadFromMemo();
    
    if(oEnvironment.getListPlaces().size() == 0)
    {
        create();
    }      
}

void VirtualEnvironment::create()
{
    switch (oEnvironment.getID())
    {
        case 1:
            build6RoomTest();
            break;

        case 2:
            build7RoomTest();
            break;

        case 3:
            build8RoomTest();
            break;            
    }
        
    storeInMemo();
}

void VirtualEnvironment::storeInMemo()
{    
    oEnvironment.storeInMemo();
}

void VirtualEnvironment::loadFromMemo()
{    
    oEnvironment.loadFromMemo();
}

std::vector<Connection>& VirtualEnvironment::getPresentConnections()
{
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
    
    // 0 -> 4
    oConnection.set(0, 4, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.set(1, 3, ConnectionType::eTYPE_SUBIDA_LARGA);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.set(1, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.set(2, 3, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.set(3, 1, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.set(3, 2, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.set(3, 4, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.set(4, 0, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.set(4, 3, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 5
    oConnection.set(4, 5, ConnectionType::eTYPE_BAJADA_CORTA);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.set(5, 1, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 4    
    oConnection.set(5, 4, ConnectionType::eTYPE_SUBIDA_CORTA);
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
    
    // 0 -> 4
    oConnection.set(0, 4, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.set(1, 3, ConnectionType::eTYPE_SUBIDA_LARGA);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.set(1, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.set(2, 3, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.set(3, 1, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.set(3, 2, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.set(3, 4, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.set(4, 0, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.set(4, 3, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 6
    oConnection.set(4, 6, ConnectionType::eTYPE_BAJADA_CORTA);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.set(5, 1, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 6    
    oConnection.set(5, 6, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 6 -> 4
    oConnection.set(6, 4, ConnectionType::eTYPE_SUBIDA_CORTA);
    oPlace6.addConnection(oConnection);
    
    // 6 -> 5    
    oConnection.set(6, 5, ConnectionType::eTYPE_PLANO_CORTO);
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
    
    // 0 -> 4
    oConnection.set(0, 4, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.set(1, 3, ConnectionType::eTYPE_SUBIDA_LARGA);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.set(1, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    oConnection.set(2, 3, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.set(3, 1, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.set(3, 2, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace3.addConnection(oConnection);
    
    // 3 -> 4
    oConnection.set(3, 4, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace3.addConnection(oConnection);

    // 4 -> 0
    oConnection.set(4, 0, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace4.addConnection(oConnection);  
    
    // 4 -> 3
    oConnection.set(4, 3, ConnectionType::eTYPE_PLANO_LARGO);
    oPlace4.addConnection(oConnection); 
    
    // 4 -> 6
    oConnection.set(4, 6, ConnectionType::eTYPE_BAJADA_CORTA);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.set(5, 1, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 7    
    oConnection.set(5, 7, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 6 -> 4
    oConnection.set(6, 4, ConnectionType::eTYPE_SUBIDA_CORTA);
    oPlace6.addConnection(oConnection);
    
    // 6 -> 7   
    oConnection.set(6, 7, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace6.addConnection(oConnection);
    
    // 7 -> 5
    oConnection.set(7, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace7.addConnection(oConnection);
    
    // 7 -> 6   
    oConnection.set(7, 6, ConnectionType::eTYPE_PLANO_CORTO);
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

}