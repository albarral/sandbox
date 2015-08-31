/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "VirtualEnvironment.h"
#include "types/ConnectionType.h"

namespace sam 
{
log4cxx::LoggerPtr VirtualEnvironment::logger(log4cxx::Logger::getLogger("sam.navigation"));

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
    
    // if not in DB, create it
    if (oEnvironment.getListPlaces().size() == 0)
    {
        create();
    }      
    
    describeEnvironment(&oEnvironment);    
}

void VirtualEnvironment::create()
{
    switch (oEnvironment.getID())
    {
        case eENV_6ROOM:
            build6RoomTest();
            break;

        case eENV_7ROOM:
            build7RoomTest();
            break;

        case eENV_8ROOM:
            build8RoomTest();
            break;     
         
        case eENV_9ROOM:
            build9RoomTest();
            break; 
            
        default:
            // invalid value
            return;
    }
        
    storeInMemo();
}

void VirtualEnvironment::storeInMemo()
{    
    oEnvironment.storeInMemo();
}

void VirtualEnvironment::loadFromMemo()
{    
    LOG4CXX_INFO(logger, "Loading environment from DB ...");    
    oEnvironment.loadFromMemo();        
}

void VirtualEnvironment::storeLearned()
{    
    oEnvironment.storeQ();
}

std::vector<Connection>& VirtualEnvironment::getPresentConnections()
{
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    return mPlaceNow.getListConnections();
}

std::vector<Place>& VirtualEnvironment::getPresentPlaces()
{
    return oEnvironment.getListPlaces();
}

void VirtualEnvironment::crossConnection(int connectionID)
{
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    Connection& mConnection = mPlaceNow.getListConnections().at(connectionID);
    setPlaceNow(mConnection.getNextPlace());
}  

void VirtualEnvironment::describeEnvironment(Environment* pEnvironment)
{       
    // describe the enviroment
    LOG4CXX_INFO(logger, pEnvironment->showData());
    
    // describe its places
    std::vector<Place>::iterator it_place = pEnvironment->getListPlaces().begin();
    std::vector<Place>::iterator it_end = pEnvironment->getListPlaces().end();
    while (it_place != it_end)
    {
        describePlace(&(*it_place));
        it_place++;
    }    
}

void VirtualEnvironment::describePlace(Place* pPlace)
{       
    // describe the place
    LOG4CXX_INFO(logger, pPlace->showData());

    // describe its connections
    std::vector<Connection>::iterator it_conn = pPlace->getListConnections().begin();
    std::vector<Connection>::iterator it_end = pPlace->getListConnections().end();
    while (it_conn != it_end)
    {
        LOG4CXX_INFO(logger, it_conn->showData());
        it_conn++;
    }    
}


void VirtualEnvironment::build6RoomTest()
{
    //    1--\
    //    |   \
    // 2--3    5
    //    |   /
    // 0--4--/
    
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5;
    Connection oConnection;
    int envID = oEnvironment.getID();
    
    LOG4CXX_INFO(logger, "Building 6 room environment ... envID=" << envID);    

    oEnvironment.setDesc("6 room");
    oPlace0.setID(0);  
    oPlace0.setEnvironmentID(envID);
    oPlace0.setReward(0);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(envID);
    oPlace1.setReward(0);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(envID);
    oPlace2.setReward(0);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(envID);
    oPlace3.setReward(0);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(envID);
    oPlace4.setReward(0);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(envID);
    oPlace5.setReward(0);
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(envID);
    
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
    
    LOG4CXX_INFO(logger, oPlace0.showData());
    LOG4CXX_INFO(logger, oPlace1.showData());
    LOG4CXX_INFO(logger, oPlace2.showData());
    LOG4CXX_INFO(logger, oPlace3.showData());
    LOG4CXX_INFO(logger, oPlace4.showData());
    LOG4CXX_INFO(logger, oPlace5.showData());

    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);

    LOG4CXX_INFO(logger, "environment built");       
}

void VirtualEnvironment::build7RoomTest()
{   
    //    1--5--\
    //    |      \
    // 2--3       6
    //    |      /
    // 0--4-----/
    
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5, oPlace6;
    Connection oConnection;
    int envID = oEnvironment.getID();

    LOG4CXX_INFO(logger, "Building 7 room environment ... envID=" << envID);    

    oEnvironment.setDesc("7 room");
    oPlace0.setID(0); 
    oPlace0.setEnvironmentID(envID);
    oPlace0.setReward(0);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(envID);
    oPlace1.setReward(0);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(envID);
    oPlace2.setReward(0);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(envID);
    oPlace3.setReward(0);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(envID);
    oPlace4.setReward(0);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(envID);
    oPlace5.setReward(0);
    oPlace6.setID(6);
    oPlace6.setEnvironmentID(envID);
    oPlace6.setReward(0);
    
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(envID);
    
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
    oConnection.set(2, 3, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    oConnection.set(3, 1, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace3.addConnection(oConnection);    

    // 3 -> 2
    oConnection.set(3, 2, ConnectionType::eTYPE_SUBIDA_LARGA);
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
    
    LOG4CXX_INFO(logger, oPlace0.showData());
    LOG4CXX_INFO(logger, oPlace1.showData());
    LOG4CXX_INFO(logger, oPlace2.showData());
    LOG4CXX_INFO(logger, oPlace3.showData());
    LOG4CXX_INFO(logger, oPlace4.showData());
    LOG4CXX_INFO(logger, oPlace5.showData());
    LOG4CXX_INFO(logger, oPlace6.showData());
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    oEnvironment.addPlace(oPlace6);
  
    LOG4CXX_INFO(logger, "environment built");       
}

void VirtualEnvironment::build8RoomTest()
{
    //    1--5\
    //    |    \
    // 2--3     7
    //    |    /
    // 0--4--6/
    
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5, oPlace6, oPlace7;
    Connection oConnection;
    int envID = oEnvironment.getID();

    LOG4CXX_INFO(logger, "Building 8 room environment ... envID=" << envID);    

    oEnvironment.setDesc("8 room");
    oPlace0.setID(0); 
    oPlace0.setEnvironmentID(envID);
    oPlace0.setReward(0);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(envID);
    oPlace1.setReward(0);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(envID);
    oPlace2.setReward(0);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(envID);
    oPlace3.setReward(0);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(envID);
    oPlace4.setReward(0);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(envID);
    oPlace5.setReward(0);
    oPlace6.setID(6);
    oPlace6.setEnvironmentID(envID);
    oPlace6.setReward(0);
    oPlace7.setID(7);
    oPlace7.setEnvironmentID(envID);
    oPlace7.setReward(0);
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(envID);
    
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
    
    LOG4CXX_INFO(logger, oPlace0.showData());
    LOG4CXX_INFO(logger, oPlace1.showData());
    LOG4CXX_INFO(logger, oPlace2.showData());
    LOG4CXX_INFO(logger, oPlace3.showData());
    LOG4CXX_INFO(logger, oPlace4.showData());
    LOG4CXX_INFO(logger, oPlace5.showData());
    LOG4CXX_INFO(logger, oPlace6.showData());
    LOG4CXX_INFO(logger, oPlace7.showData());
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    oEnvironment.addPlace(oPlace6);
    oEnvironment.addPlace(oPlace7);
  
    LOG4CXX_INFO(logger, "environment built");       
}

void VirtualEnvironment::build9RoomTest()
{
    //    1-\--7-\
    //    |  \    8
    // 2--3   5--/
    //    |  /
    // 0--4-/--6
    
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5, oPlace6, oPlace7, oPlace8;
    Connection oConnection;
    int envID = oEnvironment.getID();

    LOG4CXX_INFO(logger, "Building 9 room environment ... envID=" << envID);    

    oEnvironment.setDesc("9 room");
    oPlace0.setID(0); 
    oPlace0.setEnvironmentID(envID);
    oPlace0.setReward(0);
    oPlace1.setID(1);   
    oPlace1.setEnvironmentID(envID);
    oPlace1.setReward(0);
    oPlace2.setID(2);
    oPlace2.setEnvironmentID(envID);
    oPlace2.setReward(0);
    oPlace3.setID(3);    
    oPlace3.setEnvironmentID(envID);
    oPlace3.setReward(0);
    oPlace4.setID(4);    
    oPlace4.setEnvironmentID(envID);
    oPlace4.setReward(0);
    oPlace5.setID(5);
    oPlace5.setEnvironmentID(envID);
    oPlace5.setReward(0);
    oPlace6.setID(6);
    oPlace6.setEnvironmentID(envID);
    oPlace6.setReward(0);
    oPlace7.setID(7);
    oPlace7.setEnvironmentID(envID);
    oPlace7.setReward(0);
    oPlace8.setID(8);
    oPlace8.setEnvironmentID(envID);
    oPlace8.setReward(0);
   
    // default connection properties for an office environment
    oConnection.setEnvironmentID(envID);
    
    // 0 -> 4
    oConnection.set(0, 4, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace0.addConnection(oConnection);

    // 1 -> 3
    oConnection.set(1, 3, ConnectionType::eTYPE_SUBIDA_LARGA);
    oPlace1.addConnection(oConnection);   
    
    // 1 -> 5
    oConnection.set(1, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace1.addConnection(oConnection);
    
    // 1 -> 7
    oConnection.set(1, 7, ConnectionType::eTYPE_PLANO_CORTO);
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
    oConnection.set(4, 5, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace4.addConnection(oConnection);
    
    // 4 -> 6
    oConnection.set(4, 6, ConnectionType::eTYPE_BAJADA_CORTA);
    oPlace4.addConnection(oConnection);
  
    // 5 -> 1
    oConnection.set(5, 1, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 4    
    oConnection.set(5, 4, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace5.addConnection(oConnection);
    
    // 5 -> 8    
    oConnection.set(5, 8, ConnectionType::eTYPE_SUBIDA_LARGA);
    oPlace5.addConnection(oConnection);
    
    // 6 -> 4
    oConnection.set(6, 4, ConnectionType::eTYPE_SUBIDA_CORTA);
    oPlace6.addConnection(oConnection);
    
    // 7 -> 1
    oConnection.set(7, 1, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace7.addConnection(oConnection);
    
    // 7 -> 8   
    oConnection.set(7, 8, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace7.addConnection(oConnection);
    
    // 8 -> 5
    oConnection.set(8, 5, ConnectionType::eTYPE_BAJADA_LARGA);
    oPlace8.addConnection(oConnection);
    
    // 8 -> 7   
    oConnection.set(8, 7, ConnectionType::eTYPE_PLANO_CORTO);
    oPlace8.addConnection(oConnection);
    
    LOG4CXX_INFO(logger, oPlace0.showData());
    LOG4CXX_INFO(logger, oPlace1.showData());
    LOG4CXX_INFO(logger, oPlace2.showData());
    LOG4CXX_INFO(logger, oPlace3.showData());
    LOG4CXX_INFO(logger, oPlace4.showData());
    LOG4CXX_INFO(logger, oPlace5.showData());
    LOG4CXX_INFO(logger, oPlace6.showData());
    LOG4CXX_INFO(logger, oPlace7.showData());
    LOG4CXX_INFO(logger, oPlace8.showData());
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
    oEnvironment.addPlace(oPlace6);
    oEnvironment.addPlace(oPlace7);
    oEnvironment.addPlace(oPlace8);
  
    LOG4CXX_INFO(logger, "environment built");       
}

}