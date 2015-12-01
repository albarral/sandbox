/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/GameAnalyser.h"
#include "sam/player/modules/watch/BoardWatcher.h"
#include "sam/player/data/T3Board.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr GameAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

GameAnalyser::GameAnalyser() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    requiredStableTime = 2;
    pGameBoard = 0;
}

void GameAnalyser::init(GameBoard& oGameBoard, GameAction& oGameAction)
{
    pGameBoard = &oGameBoard;
    pGameAction = &oGameAction;
    matBoard = pGameBoard->getMatrixClone();
    binitialized = true;
    LOG4CXX_INFO(logger, "GameAnalyser initialized");     
};

void GameAnalyser::first()
{    
    log4cxx::NDC::push("GameAnalyser");   	
    log4cxx::NDC::push("()");   	

    // we start in WAITING state
    if (binitialized && isConnected())
    {
        LOG4CXX_INFO(logger, "first ... ");  
        setState(GameAnalyser::eSTATE_DONE);    
        showStateChange();        
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        Module::off();        
    }
}

void GameAnalyser::loop()
{   
    // read bus
    senseBus();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case GameAnalyser::eSTATE_WAIT:
                        
            // if board is stable (changes have finished)
            if (checkBoardStable())
            {
                // fetch new changed lines & add them to the check list
                fetchBoardData();
                // and -> ANALYSE
                setState(GameAnalyser::eSTATE_ANALYSE);                    
            }            
            break;
            
        case GameAnalyser::eSTATE_ANALYSE:

            // if board still stable 
            if (checkBoardStable())
            {
                // do analysis
                doAnalysis();         
                // and -> DONE
                setState(GameAnalyser::eSTATE_DONE);              
            }
            // but if board is changing -> WAIT
            else               
                setState(GameAnalyser::eSTATE_WAIT);              
            break;

        case GameAnalyser::eSTATE_DONE:
                        
            // if board is changing -> WAIT
            if (watcherState == BoardWatcher::eSTATE_CHANGING)
                setState(GameAnalyser::eSTATE_WAIT);              
            break;
    }   // end switch    
    
    if (isStateChanged())
    {
        showStateChange();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void GameAnalyser::senseBus()
{
    // read controls IN: 
    // CO_ANALYSER_INHIBIT
    binhibited = pBus->getCOBus().getCO_ANALYSER_INHIBIT().checkRequested();
    binhibited = true;
    // CO_ANALYSE_FULL
    bFullAnalysis = pBus->getCOBus().getCO_ANALYSE_FULL().checkRequested();
    
    // read sensors IN: 
    // SO_WATCHER_STATE
    watcherState = pBus->getSOBus().getSO_WATCHER_STATE().getValue();
    // SO_STABLE_TIME
    stableTime = pBus->getSOBus().getSO_STABLE_TIME().getValue(); 
}

void GameAnalyser::writeBus()
{
    // write sensors OUT: 
    // SO_ANALYSER_STATE    
    pBus->getSOBus().getSO_ANALYSER_STATE().setValue(getState());
}

bool GameAnalyser::checkBoardStable()
{
    return (watcherState == BoardWatcher::eSTATE_STABLE && stableTime >= requiredStableTime);
}

void GameAnalyser::fetchBoardData()
{
    // fetch the new board info 
    std::vector<BoardZone> listChangedLines;  
    pGameBoard->fetchInfo(matBoard, listChangedLines);
    // update the list of lines to check
    lines2Check.insert(lines2Check.end(), listChangedLines.begin(), listChangedLines.end());
    // inform the watcher module its change detection is being processed (through CO_WATCHER_ACK)
    pBus->getCOBus().getCO_WATCHER_ACK().request();    
}

void GameAnalyser::doAnalysis()
{
    LOG4CXX_INFO(logger, "do analysis ...");     
    // analyse each of the lines in the check list
    while (!lines2Check.empty())
    {        
        BoardZone& oZone = lines2Check.front();
                
        // extract the proper line data from the board matrix
        cv::Mat matLine;
        switch (oZone.getType())
        {
            case T3Board::eTYPE_ROW:
                matLine = matBoard.row(oZone.getOrdinal());
                break;
                
            case T3Board::eTYPE_COL:
                matLine = matBoard.col(oZone.getOrdinal());
                break;
                
            case T3Board::eTYPE_MAIN_DIAGONAL:
                matLine = matBoard.diag(0);
                break;
                
            case T3Board::eTYPE_ANTI_DIAGONAL:
                // a matrix antidiagonal is the main diagonal of the matrix's vertical flip
                cv::Mat matFlip = matBoard.clone();
                // fast vertical flip
                matBoard.row(0).copyTo(matFlip.row(2));
                matBoard.row(2).copyTo(matFlip.row(0));
                matLine = matFlip.diag(0);
                break;                
        }
        
        // analyse line ...
        LOG4CXX_INFO(logger, "analyse line " << oZone.getID());    
        LOG4CXX_INFO(logger, matLine);    
        // LineAnalyser ...
        
        lines2Check.pop_front();
    }
}


// Shows the next state name
void GameAnalyser::showStateChange()
{
    std::string stateName;
    switch (getState())
    {
        case GameAnalyser::eSTATE_WAIT:
            stateName = "(wait)";
            break;
            
        case GameAnalyser::eSTATE_ANALYSE:
            stateName = "(analyse)";
            break;

        case GameAnalyser::eSTATE_DONE:
            stateName = "(done)";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(stateName);   	
}

}
}