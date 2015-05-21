
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Database.h"

namespace sam 
{
Database::Database() 
{
    binitialized = false;
}

void Database::init(std::string url, std::string user, std::string password, std::string database)
{
    setURL(url);
    setUser(user, password);
    setTargetDatabase(database);
    binitialized = true;    
}

sql::Connection* Database::getConnectionDB()
{
    driver = get_driver_instance();
    con = driver -> connect(url, user, password); 
    /* turn off the autocommit */
    con -> setAutoCommit(0);
    
    return con;
}

void Database::closeConnectionDB()
{
    delete res; // segmentation fault al store
    delete stmt; // segmentation fault al store
//    delete prep_stmt;  //Segmentation fault cuando recupero datos
    con -> close();
    delete con;
}

void Database::insertToDB(std::string insert, sql::Connection *con)
{ 
    con->setSchema(database);    
    prep_stmt = con -> prepareStatement (insert);    
    prep_stmt->execute();   
}

void Database::updateDB(std::string update, sql::Connection *con)
{   
    con->setSchema(database);   
    prep_stmt = con -> prepareStatement (update);    
    prep_stmt->execute();
}

void Database::deleteDB(std::string deleteDb, sql::Connection *con)
{
    con->setSchema(database);    
    prep_stmt = con -> prepareStatement (deleteDb);
    prep_stmt->execute();
}

sql::ResultSet* Database::selectFrom(std::string select, sql::Connection *con)
{  
    con->setSchema(database);   
    stmt = con -> createStatement();   
    res = stmt->executeQuery(select);   

    return res;
}

}