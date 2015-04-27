/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include <iostream>
#include "VirtualEnvironment.h"

VirtualEnvironment::VirtualEnvironment() 
{
    placeNow = 0;
}

void VirtualEnvironment::build6RoomTest()
{
    Place oPlace0, oPlace1, oPlace2, oPlace3, oPlace4, oPlace5;
    Connection oConnection;
    oEnvironment.setID(1);
    
    cout << "6 room environment" <<endl;

    oPlace0.setID(0);    
    oPlace1.setID(1);    
    oPlace2.setID(2);
    oPlace3.setID(3);    
    oPlace4.setID(4);    
    oPlace5.setID(5);
   
    // default connection properties for an office environment
    oConnection.setLength(5);
    oConnection.setSlope(0);
    oConnection.setAbruptness(0);
    
    // 0 -> 4
    //oConnection.setID(1);
    oConnection.setPlaceID(0);
    oConnection.setNextPlace(4);
    oPlace0.addConnection(oConnection);
    
    // 1 -> 3
    //oConnection.setID(2);
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(3);
    oPlace1.addConnection(oConnection);    
    // 1 -> 5
    //oConnection.setID(3);
    oConnection.setNextPlace(5);
    oPlace1.addConnection(oConnection);
    
    // 2 -> 3
    //oConnection.setID(4);
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(3);
    oPlace2.addConnection(oConnection);
    
    // 3 -> 1
    //oConnection.setID(5);
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(1);
    oPlace3.addConnection(oConnection);    
    // 3 -> 2
    //oConnection.setID(6);
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);
    // 3 -> 4
    //oConnection.setID(7);
    oConnection.setNextPlace(4);
    oPlace3.addConnection(oConnection);
    
    // 4 -> 0
    //oConnection.setID(8);
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(0);
    oPlace4.addConnection(oConnection);        
    // 4 -> 3
    //oConnection.setID(9);
    oConnection.setNextPlace(3);
    oPlace4.addConnection(oConnection);        
    // 4 -> 5
    //oConnection.setID(10);
    oConnection.setNextPlace(5);
    oPlace4.addConnection(oConnection);
    
    // 5 -> 1
    //oConnection.setID(11);
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace5.addConnection(oConnection);
    // 5 -> 4    
    //oConnection.setID(12);
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

    cout << "environment built" << endl << endl;;       
}

std::vector<Connection>& VirtualEnvironment::getPresentConnections()
{
    int connectionID;
    //int placenow = getPlaceNow();
    
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    return mPlaceNow.getListConnections();
//    
//    vector<Connection>::iterator it_connections = mPlaceNow.getListConnections().begin();
//    vector<Connection>::iterator it_end = mPlaceNow.getListConnections().end();
//    // walk the list getting the connection IDs
//    while (it_connections != it_end)
//    {
//        connectionID = it_connections->getID();
//        cout<< "Connection: " <<connectionID<<endl;
//        listConnectionIDs.push_back(connectionID);
//        it_connections++;	
//    }
//    
//    return listConnectionIDs; //Devuelve la última ID de Connection, no el Place al que ha de ir
}

void VirtualEnvironment::crossConnection(int connectionID) // de la connectionID tengo que coger el nextPlace
{
    //int placenow = getPlaceNow();  
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placeNow);
    Connection& mConnection = mPlaceNow.getListConnections().at(connectionID); //Peta esta línea
    //int nxtPlc = mConID.getNextPlace();
    //placeNow = nxtPlc;
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
