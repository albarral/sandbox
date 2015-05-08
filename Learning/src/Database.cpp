
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "Database.h"

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *prep_stmt;
sql::Savepoint *savept;

namespace sam 
{
Database::Database() 
{}

int Database::getConnectionDB()
{
    driver = get_driver_instance();
    con = driver -> connect(url, user, password); 
}

void Database::closeConnectionDB()
{
    delete res;
    delete stmt;
    delete prep_stmt;
    con -> close();
    delete con;
}

void Database::insertToDB(std::string insert)
{
    Database::getConnectionDB();
    
    con->setSchema(database);
    
    prep_stmt = con -> prepareStatement (insert);
    
    prep_stmt->execute();
    
    Database::closeConnectionDB();
    
}
void Database::upDateDB(std::string)
{
    
}
void Database::deleteDB(std::string)
{
    
}

}