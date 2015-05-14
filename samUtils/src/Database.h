#ifndef __DATABASE_H
#define __DATABASE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
class Database
{  
private:
    bool binitialized;
    std::string url; //  "tcp://127.0.0.1:3306";
    std::string user;
    std::string password;
    std::string database;
        
public:
    Database();
    
    void init (std::string url, std::string user, std::string password, std::string database);
    
    bool isInitialized() {return binitialized;};
    void setURL(std::string value) {url = value;}
    void setUser(std::string value1, std::string value2) {user = value1; password = value2;};
    void setTargetDatabase(std::string value) {database = value;};
    
    int getConnectionDB();
    void closeConnectionDB();
    void insertToDB(std::string);
    void updateDB(std::string);
    void deleteDB(std::string);

};
}

#endif
