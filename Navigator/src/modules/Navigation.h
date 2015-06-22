#ifndef __SAM_NAVIGATION_H
#define __SAM_NAVIGATION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "utils/module2.h"
#include "VirtualEnvironment.h"
#include "Connection.h" // learning module
#include "Learn.h"
#include "Experiment.h"

namespace sam 
{
// Module that performs smart navigation through an environment.
// It derives from base class Module2
// It has 3 states:
// STOP       - waits for a new task request    
// GO           - traverses the environment in search for the target place
// REACHED  - target place reached
class Navigation : public Module2
{
public:
    // states of Navigation module
    enum eType
    {
         eSTATE_STOP, 
         eSTATE_GO, 
         eSTATE_REACHED
    };

    // strategies of Navigation module
    enum eStrategy
    {
         eSTRAT_RANDOM, 
         eSTRAT_LOWER_COST, 
         eSTRAT_SMART,
         eSTRAT_UNKNOWN
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // logic
    int strategy;       // used navigation strategy
    int targetPlace;   // navigation target 
    int numSteps;    // steps performed in the last navigation task
    VirtualEnvironment* pVirtualEnvironment;    // to be replaced by VirtualTask in the future
    Learn oLearn;

public:
    Navigation();
    //~Navigation();
    
    // initializes the module 
    void init (VirtualEnvironment& oVirtualEnvironment);       
    bool isEnabled() {return benabled;};
    void storeLearned();

    // starts a new navigation task towards the specifed target using the specified strategy (eStrategy)
    void newTask(int targetPlace, int strategy);       
    // returns the present place where the agent is located
    int getLocation();
    // gets the number of steps performed
    int getNumSteps() {return numSteps;}
    // returns the name of the strategy
    std::string getStrategyName();

private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();                
    // advances to an other place in search of the target
    void nextStep();
    
    // LEARNING methods ... 
    // selects the connection to be taken according to the active navigation strategy
    int selectConnection();
    Connection* getRandomConnection(std::vector<Connection>& listConnections);
    Connection* getSmartestConnection(std::vector<sam::Connection>& listConnections);
    Connection* getBestConnection(std::vector<Connection>& listConnections);
    float computeConfidence(float cost);
    
    // shows the present state name
    void showState();    
    
};
}
#endif
