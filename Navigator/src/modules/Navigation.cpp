/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <cstdlib>  //for the random values
#include "log4cxx/ndc.h"
#include "opencv2/core/core.hpp" //for the matrix

#include "Navigation.h"
#include "nav/LearnNav.h"

namespace sam 
{
log4cxx::LoggerPtr Navigation::logger(log4cxx::Logger::getLogger("sam.navigation"));

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
    // sets new target, strategy and exploration mode
    this->targetPlace = targetPlace;   
    if (strategy < eSTRAT_UNKNOWN)   
        this->strategy = strategy;
    else
        this->strategy = eSTRAT_RANDOM;
    
    // forces the next state to be GO
    numSteps = 0;
    setNextState(eSTATE_GO);

    LOG4CXX_INFO(logger, "new navigation task: target=" << this->targetPlace << ", strategy=" << getStrategyName());      
}

void Navigation::stopTask()
{
    setNextState(eSTATE_STOP);
}

int Navigation::getLocation()
{
    return pVirtualEnvironment->getPlaceNow();
}

void Navigation::nextStep()
{
    // selects a path departing from the present place & traverses it to reach a new place    
    int nextConnection = selectConnection();
    previousPlace = pVirtualEnvironment->getPlaceNow();
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
            winner = getLowerCostConnection(pVirtualEnvironment->getPresentConnections());
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
    // selects a random connection from the given list, avoiding going back to the previous place
    sam::Connection* winner = 0;   
    int randNumConn, size;
    bool bNewPlaceFound = false;
   
    size = listConnections.size();
    randNumConn = rand() % size;

    if (size == 1)
    {
        winner = &(listConnections.at(0));
    }    
    else 
    {
        while (!bNewPlaceFound)
        {
            randNumConn = rand() % size;
            bNewPlaceFound = listConnections.at(randNumConn).getNextPlace() != previousPlace;
        }        
        winner = &(listConnections.at(randNumConn));
    }
    showConnections(listConnections);

    return winner;    
}

// IMPORTANT: this method will be moved to the Learning project in the future
Connection* Navigation::getLowerCostConnection(std::vector<sam::Connection>& listConnections)
{
    // checks all connections in the given list and gets the one with highest confidence (a combination of Q and cost)
    sam::Connection* winner = 0;
    sam::Connection* winnerTemporal = 0;
    std::vector<sam::Connection> listWinners;
    float maxConfidence = 0;
    float confidence, cost, Q;
    int randNumConn;

    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        Connection& oConnection = *it_connection;
        Q = calculateQvalue(oConnection);
        // update connection's Q
        oConnection.setQ(Q);
        
        cost = oConnection.computeCost();
        confidence = computeConfidence(cost);                
        LOG4CXX_INFO(logger, "connects to " <<  it_connection->getNextPlace() << " - "  << it_connection->getDesc() << ", cost=" << cost <<  ", conf=" << confidence << ", Q = " << Q);  
        
        // the connection with highest confidence is the winner
        if (confidence > maxConfidence)
        {
            maxConfidence = confidence;
            listWinners.clear();
            listWinners.push_back(oConnection);
            winner = &oConnection;
        }        
        // if various connections share the maximum confidence, take winner randomly among them
        else if (confidence == maxConfidence)
        {
            listWinners.push_back(oConnection);
            
            randNumConn = rand() % listWinners.size();
            winnerTemporal = &(listWinners.at(randNumConn));
            winner = &(listConnections.at(winnerTemporal->getID()));
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
    sam::Connection* winnerTemporal = 0;
    std::vector<sam::Connection> listWinners;
    float maxConfidence = 0, Q;
    int randNumConn;

    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {   
        Connection& oConnection = *it_connection;
        Q = calculateQvalue(oConnection);
        // update connection's Q
        oConnection.setQ(Q);
        
        LOG4CXX_INFO(logger, "connects to " << it_connection->getNextPlace() << " - "  << it_connection->getDesc() << ", Q = " << Q);      
           
        // the connection with highest confidence is the winner
        if (Q > maxConfidence)
        {
            maxConfidence = Q;
            listWinners.clear();
            listWinners.push_back(oConnection);
            winner = &oConnection;
        }      
        // if various connections share the maximum confidence, take winner randomly among them
        else if (Q == maxConfidence)
        {
            listWinners.push_back(oConnection);
            
            randNumConn = rand() % listWinners.size();
            winnerTemporal = &(listWinners.at(randNumConn));
            winner = &(listConnections.at(winnerTemporal->getID()));
        }
        it_connection++;
    }   
    return winner;
}

void Navigation::showConnections(std::vector<sam::Connection>& listConnections)
{
    float Q;
    std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
    std::vector<sam::Connection>::iterator it_end = listConnections.end();
    while (it_connection != it_end)
    {
        Q = calculateQvalue(*it_connection);
        LOG4CXX_INFO(logger, "connects to " <<  it_connection->getNextPlace() << " - "  << it_connection->getDesc() << ", Q = " << Q);
        it_connection++;
    }
}

// computes the Q value of given connection (using the info from next place)
float Navigation::calculateQvalue(Connection& oConnection)
{
    std::vector<sam::Place>& listPlaces = pVirtualEnvironment->getPresentPlaces();    
    Place& oNextPlace = listPlaces.at(oConnection.getNextPlace());    
    
    return oLearn.computeQ(oNextPlace);
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

void Navigation::storeLearned()
{
    pVirtualEnvironment->storeLearned();
}

void Navigation::showLearned()
{    
    std::vector<sam::Place>& listPlaces = pVirtualEnvironment->getPresentPlaces();
    std::vector<sam::Place>::iterator it_places = listPlaces.begin();
    std::vector<sam::Place>::iterator it_endP = listPlaces.end();
    
    int i = listPlaces.size();
    cv::Mat Q = cv::Mat_<int>(cv::Mat::zeros(i,i, CV_8U));
    
    while (it_places != it_endP)
    {
        std::vector<sam::Connection>& listConnections = listPlaces.at(it_places->getID()).getListConnections();
        std::vector<sam::Connection>::iterator it_connection = listConnections.begin();
        std::vector<sam::Connection>::iterator it_endC = listConnections.end();
        while (it_connection != it_endC)
        {
            int j = it_places->getID();
            int z = it_connection->getNextPlace();
            
            Q.at<int>(j,z) = it_connection->getQ();
            it_connection++;
        }
        it_places++;
    }
    
    LOG4CXX_INFO(logger, " Matrix Q:\n " << Q);
}

}