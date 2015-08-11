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
#include "Connection.h" 
#include "Learn.h"  // learning module

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
    bool bexploration;  // exploration mode (when active it will select random connections, instead of the best ones)
    int targetPlace;   // navigation target 
    int numSteps;    // steps performed in the last navigation task
    int previousPlace; // save the state where it is before doing the next step
    VirtualEnvironment* pVirtualEnvironment;    // to be replaced by VirtualTask in the future
    Learn oLearn;

public:
    Navigation();
    //~Navigation();
    
    // initializes the module 
    void init (VirtualEnvironment& oVirtualEnvironment);       
    bool isEnabled() {return benabled;};

    // starts a new navigation task towards the specified target using the specified strategy (eStrategy)
    // also sets the exploration mode 
    void newTask(int targetPlace, int strategy);
    //stop the navigation task
    void stopTask();
    // returns the present place where the agent is located
    int getLocation();
    // gets the number of steps performed
    int getNumSteps() {return numSteps;}
    // gets strategy code
    int getStrategy() {return strategy;};
    
    // show the connections in the random case with the values of Q
    void showConnections(std::vector<Connection>& listConnections);
    // method to do the call to learn to calculate the value of Q
    float calculateQvalue(Connection* pConnection);
    // stores learned Qs for environment connections
    void storeLearned();
    // show a matrix with the values of Qs
    void showLearned();

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
    // returns the name of the strategy
    std::string getStrategyName();
    
};
}
#endif
