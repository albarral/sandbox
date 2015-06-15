/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <cstdlib>  //for the random values
#include "log4cxx/ndc.h"

#include "Navigation.h"
#include "Learn.h"

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
    oLearn.setGamma(0.8);

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
            winner = getBestConnection(pVirtualEnvironment->getPresentConnections());
            break; 
            
        case eSTRAT_SMART:
            winner = getSmartestConnection(pVirtualEnvironment->getPresentConnections());
            break;                        
    }
    
    LOG4CXX_INFO(logger, "selected -> " << winner->getNextPlace());
    return winner->getID();
}

// IMPORTANT: this method will be moved to the Learning project in the future
Connection* Navigation::getRandomConnection(std::vector<sam::Connection>& listConnections)
{
    sam::Connection* winner = 0;
    
    int randNumConn, size;
    
    size = listConnections.size();
    randNumConn = rand() % size;
    
    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        LOG4CXX_INFO(logger, "connects to " << it_connection->getNextPlace() << " - "  << it_connection->getDesc());
        if(randNumConn == it_connection->getID())
        {
            winner = &(*it_connection);
        }
        it_connection ++;
    }   
    return winner;    
}

// IMPORTANT: this method will be moved to the Learning project in the future
Connection* Navigation::getBestConnection(std::vector<sam::Connection>& listConnections)
{
    // checks all connections in the given list and gets the one with highest confidence (a combination of Q and cost)
    sam::Connection* winner = 0;
    float maxConfidence = -1.0;
    float confidence, cost;

    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        cost = it_connection->computeCost();
        confidence = computeConfidence(cost);                
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
Connection* Navigation::getSmartestConnection(std::vector<sam::Connection>& listConnections)
{
    // checks all connections in the given list and gets the one with highest confidence (a combination of Q and cost)
    sam::Connection* winner = 0;
    float maxConfidence = -1.0, Q;
    int nextPlace;

    std::vector<sam::Place>& listPlaces = pVirtualEnvironment->getPresentPlaces();

    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        nextPlace = it_connection->getNextPlace();
        Place &oPlace = listPlaces.at(nextPlace);
        Connection* pConnection2 = &(*it_connection);
        Q = oLearn.computeQ(pConnection2, oPlace);

        LOG4CXX_INFO(logger, "connects to " << it_connection->getNextPlace() << " - "  << it_connection->getDesc() << ", Q = " << Q);
        
        if (Q > maxConfidence)
        {
            maxConfidence = Q;
            winner = &(*it_connection);
        }        
        it_connection++;	
    }    
    return winner;
}

// IMPORTANT: this method will be moved to the Learning project in the future
float Navigation::computeConfidence(float cost)
{
    if (cost == 0) cost = 1.0; // protect against cost
    
    return (1.0/cost);    
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