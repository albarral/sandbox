/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM NAVIGATION

#include <vector>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "VirtualEnvironment.h"
#include "modules/Navigation.h" 
#include "data/Experiment.h"


log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.navigation"));

void testNavigation();
// prepares the set of navigation experiments to be performed
void setNavigationExperiments(std::vector<sam::Experiment>& listExperiments, sam::VirtualEnvironment& oVirtualEnvironment);
// performs a single navigation experiment
void doNavigationTask(sam::Navigation& oNavigation, sam::VirtualEnvironment& oVirtualEnvironment, sam::Experiment& oExperiment);


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

    LOG4CXX_INFO(logger, "*** INIT environment");    
    // init environment
    oVirtualEnvironment.init(sam::VirtualEnvironment::eENV_9ROOM);

    LOG4CXX_INFO(logger, "*** INIT navigation");
    // start navigation module
    oNavigation.init(oVirtualEnvironment);
    oNavigation.setFrequency(1.0);    
    oNavigation.on();

    sleep (1);    

    // prepare experiments
    std::vector<sam::Experiment> listExperiments;
    setNavigationExperiments(listExperiments, oVirtualEnvironment);
    
    // perform experiments
    for (int i=0; i<listExperiments.size(); i++)
    {
        sam::Experiment& oExperiment = listExperiments.at(i);
        
        doNavigationTask(oNavigation, oVirtualEnvironment, oExperiment);  
        sleep(1);
    }
    
    oNavigation.off();
    oNavigation.wait();

    LOG4CXX_INFO(logger, "End of test");    
    
    return;        
}


void doNavigationTask(sam::Navigation& oNavigation, sam::VirtualEnvironment& oVirtualEnvironment, sam::Experiment& oExperiment)
{   
    int strategy;
    LOG4CXX_INFO(logger, ">>>>>> New navigation task:");    
    LOG4CXX_INFO(logger, "From " << oExperiment.getFirstPlace() << " to " << oExperiment.getTargetPlace());
    LOG4CXX_INFO(logger, "Max steps = " << oExperiment.getMaxSteps());
    if (oExperiment.getExplorationMode())
    {    
        LOG4CXX_INFO(logger, "Exploration mode");
        strategy = sam::Navigation::eSTRAT_RANDOM;
    } 
    else strategy = sam::Navigation::eSTRAT_SMART;
    
    // set first place
    oVirtualEnvironment.setPlaceNow(oExperiment.getFirstPlace());
    // launch new navigation task
    oNavigation.newTask(oExperiment.getTargetPlace(), strategy);
        
    // wait until target reached or max steps reached
    while ((oNavigation.getState() != sam::Navigation::eSTATE_REACHED) && (oNavigation.getNumSteps() < oExperiment.getMaxSteps()))            
        sleep (1);

    if ((oNavigation.getState() != sam::Navigation::eSTATE_REACHED))
    {
        LOG4CXX_INFO(logger, "Too many steps without reaching the target !!!! " << oNavigation.getNumSteps()); 
        oNavigation.stopTask();
    }
       
    oNavigation.storeLearned();
    oNavigation.showLearned();

    LOG4CXX_INFO(logger, "End of task");
    oNavigation.stopTask();
}

void setNavigationExperiments(std::vector<sam::Experiment>& listExperiments, sam::VirtualEnvironment& oVirtualEnvironment)
{
    sam::Experiment oExperiment;
    int maxSteps = 10;
    int i, iterations = 5;
    int from = 2;   // initial place
    int to = 6;       // target place   
    
    //put reward values    
    std::vector<sam::Place>& listPlaces = oVirtualEnvironment.getPresentPlaces();
    std::vector<sam::Place>::iterator it_places = listPlaces.begin();
    std::vector<sam::Place>::iterator it_endP = listPlaces.end();
    while (it_places != it_endP)
    {
        if(it_places->getID() == to)
        {
            it_places->setReward(100);
        }
        else it_places->setReward(0);
        it_places++;
    }  
    
    // first various iterations in exploration mode
    oExperiment.setParams(from, to, maxSteps, true);
    for (i=0; i<iterations; i++)
        listExperiments.push_back(oExperiment);

    // then various iterations in normal mode
    oExperiment.setParams(from, to, maxSteps, false);
    for (i=0; i<iterations; i++)
        listExperiments.push_back(oExperiment);
}