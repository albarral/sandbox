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
    std::string url = "tcp://127.0.0.1:3306";
    const std::string user = "root";
    const std::string password = "migtron2015";
    const std::string database = "samMemo";
        
public:
    Database();
    int getConnectionDB();
    void closeConnectionDB();
    void insertToDB(std::string);
    void upDateDB(std::string);
    void deleteDB(std::string);

};
}

#endif
