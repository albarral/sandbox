/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM NAVIGATION

#include <unistd.h> // for sleep() 
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "VirtualEnvironment.h"
#include "modules/Navigation.h" 

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.navigation"));

void testNavigation();

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    testNavigation();
    
    return 0;
}


void testNavigation()
{   
    LOG4CXX_INFO(logger, "<<<<<<<<<<<<<<<< TEST NAVIGATION >>>>>>>>>>>>>>");    
    
    sam::VirtualEnvironment oVirtualEnvironment;  
    sam::Navigation oNavigation;
    int targetPlace;


    LOG4CXX_INFO(logger, "***** INIT environment");    
    // init environment
    oVirtualEnvironment.init(sam::VirtualEnvironment::eENV_6ROOM);
    oVirtualEnvironment.setPlaceNow(0);

    LOG4CXX_INFO(logger, "***** INIT navigation");    
    // start navigation module
    oNavigation.init(oVirtualEnvironment);
    oNavigation.setFrequency(1.0);    
    oNavigation.on();

    // command task
    sleep (1);    
    targetPlace = 6;
    oNavigation.newTask(targetPlace, sam::Navigation::eSTRAT_LOWER_COST);
        
    // wait until target reached or num steps > 20
    while ((oNavigation.getState() != sam::Navigation::eSTATE_REACHED) && (oNavigation.getNumSteps()<10))            
        sleep (1);

    if ((oNavigation.getState() != sam::Navigation::eSTATE_REACHED))
        LOG4CXX_INFO(logger, "Too many steps without reaching the target !!!! " << oNavigation.getNumSteps());    

    oNavigation.off();
    oNavigation.wait();

    LOG4CXX_INFO(logger, "End of test");    
  
    return ;
        
}
