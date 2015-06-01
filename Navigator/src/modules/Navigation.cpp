/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "log4cxx/ndc.h"

#include "Navigation.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr Navigation::logger(Logger::getLogger("sam.navigation"));

Navigation::Navigation()
{
    benabled = false;
}

void Navigation::init(VirtualEnvironment& oVirtualEnvironment)
{
    pVirtualEnvironment = &oVirtualEnvironment;
    benabled = true;

    LOG4CXX_INFO(logger, "Navigation module initialized");      
};

void Navigation::first()
{    
    setState(eSTATE_STOP);
    setNextState(eSTATE_STOP);    

    log4cxx::NDC::push("nav");   	
    log4cxx::NDC::push("stop");   	
    LOG4CXX_INFO(logger, "first place " << getLocation());  
}
                    
void Navigation::loop()
{
    if (updateState())
        showState();
          
    switch (getState())
    {
        case eSTATE_STOP:
            // nothing done
            break;
            
        case eSTATE_GO:
            
            nextStep();
            
            if (getLocation() == targetPlace)
                setNextState(eSTATE_REACHED);    
            break;
                    
        case eSTATE_REACHED:            
            // nothing done
            break;
    }   // end switch    
    
}


void Navigation::newTask(int targetPlace, int strategy)
{
    // sets new target & strategy, and sets the next state to GO
    this->targetPlace = targetPlace;
    
    if (strategy < eSTRAT_UNKNOWN)   
        this->strategy = strategy;
    else
        this->strategy = eSTRAT_RANDOM;
    
    numSteps = 0;
    setNextState(eSTATE_GO);

    LOG4CXX_INFO(logger, "new navigation task: target=" << this->targetPlace << ", strategy=" << getStrategyName());      
}

int Navigation::getLocation()
{
    return pVirtualEnvironment->getPlaceNow();
}

void Navigation::nextStep()
{
    // selects a path departing from the present place & traverses it to reach a new place    
    int nextConnection = selectConnection();
    pVirtualEnvironment->crossConnection(nextConnection);        
    numSteps++;
    
    LOG4CXX_INFO(logger, "new place " << getLocation());
}

// IMPORTANT: this method will be moved to the Learning project in the future
int Navigation::selectConnection()
{        
    // selects the most suitable connection from the present place in order to reach (or approach) the target
    sam::Connection* winner = 0;
    
    switch (strategy)
    {
        case eSTRAT_RANDOM:
            winner = getRandomConnection(pVirtualEnvironment->getPresentConnections());
            break;

        case eSTRAT_LOWER_COST:
        case eSTRAT_SMART:
            winner = getBestConnection(pVirtualEnvironment->getPresentConnections());
            break;                        
    }
    
    LOG4CXX_INFO(logger, "selected -> " << winner->getNextPlace());
    return winner->getID();
}

// IMPORTANT: this method will be moved to the Learning project in the future
Connection* Navigation::getRandomConnection(std::vector<sam::Connection>& listConnections)
{
    sam::Connection* winner = 0;
    
    LOG4CXX_WARN(logger, "Navigation::getRandomConnection() TO BE DEVELOPED !!! ");
    winner = &listConnections.at(0);
    
    return winner;    
}

// IMPORTANT: this method will be moved to the Learning project in the future
Connection* Navigation::getBestConnection(std::vector<sam::Connection>& listConnections)
{
    // checks all connections in the given list and gets the one with highest confidence (a combination of Q and cost)
    sam::Connection* winner = 0;
    float maxConfidence = 0.0;
    float confidence, Q, cost;
    
    Q = 0.0;  // temporal until real Learning used

    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        cost = it_connection->computeCost();
        confidence = computeConfidence(Q,cost);                
        LOG4CXX_INFO(logger, "connects to " << it_connection->getNextPlace() << " - "  << it_connection->getDesc() << ", cost=" << cost <<  ", conf=" << confidence);
        
        if (confidence > maxConfidence)
        {
            maxConfidence = confidence;
            winner = &(*it_connection);
        }        
        it_connection++;	
    }    
    return winner;
}

// IMPORTANT: this method will be moved to the Learning project in the future
float Navigation::computeConfidence(float Q, float cost)
{
    if (cost == 0) cost = 1.0; // protect against cost
    
    return (Q + (1.0/cost));    
}

void Navigation::showState()
{
    std::string stateName;
    switch (getState())
    {
        case eSTATE_STOP:
            stateName = "stop";
            break;
            
        case eSTATE_GO:
            stateName = "go";
            break;
            
        case eSTATE_REACHED:
            stateName = "reached";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(stateName);   	
}


std::string Navigation::getStrategyName()
{
    std::string strategyName;
    switch (strategy)
    {        
        case eSTRAT_RANDOM:
            strategyName = "random";
            break;                
        case eSTRAT_LOWER_COST:
            strategyName = "lower cost";
            break;            
        case eSTRAT_SMART:                        
            strategyName = "smart";                
            break;                        
        default:        
            strategyName = "none";            
    }    
    return strategyName;
}

}