/* 
 * 
 * Author: Ainoa Millán
 *
 */

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
    
    oPlace0.setID(0);    
    oPlace1.setID(1);    
    oPlace2.setID(2);
    oPlace3.setID(3);    
    oPlace4.setID(4);    
    oPlace5.setID(5);
   
    oConnection.setID(1);
    oConnection.setPlaceID(0);
    oConnection.setNextPlace(4);
    oPlace0.addConnection(oConnection);
    
    oConnection.setID(2);
    oConnection.setPlaceID(1);
    oConnection.setNextPlace(3);
    oPlace1.addConnection(oConnection);
    
    oConnection.setID(3);
    oConnection.setNextPlace(5);
    oPlace1.addConnection(oConnection);
    
    oConnection.setID(4);
    oConnection.setPlaceID(2);
    oConnection.setNextPlace(3);
    oPlace2.addConnection(oConnection);
    
    oConnection.setID(5);
    oConnection.setPlaceID(3);
    oConnection.setNextPlace(1);
    oPlace3.addConnection(oConnection);
    
    oConnection.setID(6);
    oConnection.setNextPlace(2);
    oPlace3.addConnection(oConnection);
    
    oConnection.setID(7);
    oConnection.setNextPlace(4);
    oPlace3.addConnection(oConnection);
    
    oConnection.setID(8);
    oConnection.setPlaceID(4);
    oConnection.setNextPlace(0);
    oPlace4.addConnection(oConnection);
    
    oConnection.setID(9);
    oConnection.setNextPlace(3);
    oPlace4.addConnection(oConnection);
    
    oConnection.setID(10);
    oConnection.setNextPlace(5);
    oPlace4.addConnection(oConnection);
    
    oConnection.setID(11);
    oConnection.setPlaceID(5);
    oConnection.setNextPlace(1);
    oPlace5.addConnection(oConnection);
    
    oConnection.setID(12);
    oConnection.setNextPlace(4);
    oPlace5.addConnection(oConnection);
    
    oEnvironment.addPlace(oPlace0);
    oEnvironment.addPlace(oPlace1);
    oEnvironment.addPlace(oPlace2);
    oEnvironment.addPlace(oPlace3);
    oEnvironment.addPlace(oPlace4);
    oEnvironment.addPlace(oPlace5);
       
}

int VirtualEnvironment::getConnections()
{
    int connectionID;
    int placenow = getPlaceNow();
    vector<int> listConnectionIDs;
    
    // prepare the list iterator
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placenow);
    vector<Connection>::iterator it_connections = mPlaceNow.getListConnections().begin();
    vector<Connection>::iterator it_end = mPlaceNow.getListConnections().end();
    // walk the list getting the connection IDs
    while (it_connections != it_end)
    {
        connectionID = it_connections->getID();
        cout<< "Connection: " <<connectionID<<endl;
        listConnectionIDs.push_back(connectionID);
        it_connections++;	
    }
    
    return connectionID; //Devuelve la última ID de Connection, no el Place al que ha de ir
}

void VirtualEnvironment::crossConnection(int connectionID) // de la connectionID tengo que coger el nextPlace
{
    int placenow = getPlaceNow();  
    Place& mPlaceNow = oEnvironment.getListPlaces().at(placenow);
    Connection& mConID = mPlaceNow.getListConnections().at(connectionID); //Peta esta línea
    int nxtPlc = mConID.getNextPlace();
    placeNow = nxtPlc;
}

int VirtualEnvironment::getPlaceNow() const
{ 
    return placeNow; 
}

void VirtualEnvironment::setPlaceNow(int pNow)
{
    placeNow = pNow;
}    


