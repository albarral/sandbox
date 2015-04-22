
/* 
 * 
 * Author: Ainoa Millán
 *
 */

#include <iostream>
#include <string>
#ifndef __PLACE_H
#define __PLACE_H

#include "Connection.h"
#include "opencv2/core/core.hpp"

using namespace std;

class Place
{
private:
    int ID;
    string desc;
    int environmentID;
    vector<Connection> listConnections;
    
public:
    Place();
    void addConnection(Connection& oConnection);
    void loadFromMemo();
    
    int getID() const; 
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getEnvironmentID() const;
    void setEnvironmentID(int);
    
    vector<Connection> getListConnections() const;
    void setListConnections(vector<Connection>);

   
};

#endif
