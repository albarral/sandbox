
/* 
 * 
 * Author: Ainoa Millán
 *
 */

//#include <iostream>
#include <string>
#include <vector>
#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "Place.h"
//#include "opencv2/core/core.hpp"

//using namespace std;

class Environment
{
private:
    int ID;
    string desc;
    int type;
    std::vector<Place> listPlaces;
    
public:
    Environment();
    void addPlace(Place& oPlace);
    void loadFromMemo();
    
    int getID() const;
    void setID(int);
    
    string getDesc() const;
    void setDesc(string);
    
    int getType() const;
    void setType(int);
    
    std::vector<Place>& getListPlaces();

};

#endif
