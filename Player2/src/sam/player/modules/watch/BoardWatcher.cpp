/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/watch/BoardWatcher.h"
#include "sam/player/data/T3Board.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr BoardWatcher::logger(log4cxx::Logger::getLogger("sam.player"));

BoardWatcher::BoardWatcher() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    pGameBoard = 0;
}

void BoardWatcher::init(GameBoard& oGameBoard)
{
    pGameBoard = &oGameBoard;    
    matrixSensed = pGameBoard->getMatrixCopy();
    matrixPrev = matrixSensed.clone();
    binitialized = true;
    LOG4CXX_INFO(logger, "BoardWatcher initialized");     
};

void BoardWatcher::first()
{    
    log4cxx::NDC::push("Watcher");   	
    //log4cxx::NDC::push("");   	
    
    // get all zone lists from the tic-tac-toe board 
    T3Board oT3Board;               
    listBoardRows = oT3Board.getGameZonesOfType(T3Board::eZONE_ROW);
    listBoardColumns = oT3Board.getGameZonesOfType(T3Board::eZONE_COL);
    listBoardDiagonals = oT3Board.getGameZonesOfType(T3Board::eZONE_MAIN_DIAGONAL);
    listBoardAntidiagonals = oT3Board.getGameZonesOfType(T3Board::eZONE_ANTI_DIAGONAL);

    // we start in LOST state
    if (binitialized && isConnected())
    {
        LOG4CXX_INFO(logger, "started");  
        setState(BoardWatcher::eSTATE_LOST);    
        setPrevState(BoardWatcher::eSTATE_LOST);
        showStateName();        
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        Module::off();        
    }
}

void BoardWatcher::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void BoardWatcher::loop()
{   
    // read bus
    senseBus();
    
    // skip processing if module inhibited
    if (binhibited)
        return;
              
    switch (getState())
    {
        case BoardWatcher::eSTATE_STABLE:            
                        
            // sense board
            // if found, process board info
            if (senseBoard())
            {
                processBoard();               
                // if changed, reset stable time and -> CHANGING
                if (linesChanged.size() > 0)
                {
                    setState(BoardWatcher::eSTATE_CHANGING);                    
                    resetStableTime();
                }
                // if stable, update stable time
                else
                    updateStableTime();
            }
            // if lost, reset stable time and -> LOST
            else
            {
                setState(BoardWatcher::eSTATE_LOST);
                resetStableTime();
            }            
            break;
            
        case BoardWatcher::eSTATE_CHANGING:

            // sense board
            // if found, process board info
            if (senseBoard())
            {
                processBoard();                
                // if stable, update stable time and -> STABLE
                if (linesChanged.size() == 0)
                {
                    setState(BoardWatcher::eSTATE_STABLE);                    
                    updateStableTime();
                }
            }
            // if lost -> LOST
            else
                setState(BoardWatcher::eSTATE_LOST);            
            break;

        case BoardWatcher::eSTATE_LOST:
                        
            // search board
            // if found -> CHANGING
            if (searchBoard())
                setState(BoardWatcher::eSTATE_CHANGING);                       
            break;
    }   // end switch    
    
    if (isStateChanged())
    {
        showStateName();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void BoardWatcher::senseBus()
{
    // read CI's ....
    // CO_INHIBIT_WATCHER
    binhibited = pBus->getCOBus().getCO_WATCHER_INHIBIT().checkRequested();
    // CO_WATCHER_ACK
    if (pBus->getCOBus().getCO_WATCHER_ACK().checkRequested())
    {
        // on ack received, reset changed lines
        //LOG4CXX_INFO(logger, "ack received");     
        pGameBoard->resetChangedLines();
    }
}

void BoardWatcher::writeBus()
{
    // write SO's ... 
    // SO_WATCHER_STATE
    pBus->getSOBus().getSO_WATCHER_STATE().setValue(getState());
    // SO_WATCHER_STABLETIME
    pBus->getSOBus().getSO_WATCHER_STABLETIME().setValue(timeStable);
}

void BoardWatcher::processBoard()
{
    LOG4CXX_DEBUG(logger, "check board changes ...");     

    // reset changes
    linesChanged.clear();
        
    // compare present & previous board configuration
    cv::Mat matDif = matrixSensed != matrixPrev;    
    // if board changed    
    if (cv::countNonZero(matDif) > 0)
    {
        LOG4CXX_INFO(logger, "board changed \n " << matrixSensed);     
                
        // update matrix copy
        matrixSensed.copyTo(matrixPrev);
        
        // check rows
        checkChangedRows(matDif);
        // check columns
        checkChangedColumns(matDif);
        // check diagonals
        checkChangedDiagonals(matDif);

        // store changes in shared data object
        pGameBoard->updateInfo(matrixSensed, linesChanged);
    }
}

// detect changes in rows
void BoardWatcher::checkChangedRows(cv::Mat& matDif)
{
    int numRows = listBoardRows.size();
    
    // analyse each row in matDif
    for (int i=0; i<numRows; i++)
    {
        cv::Mat matRow = matDif.row(i);
        // detecting which rows have changed
        if (cv::countNonZero(matRow) > 0)
            linesChanged.push_back(listBoardRows.at(i));
    }        
}

// detect changes in columns
void BoardWatcher::checkChangedColumns(cv::Mat& matDif)
{
    int numColumns = listBoardColumns.size();
    
    // analyse each column in matDif 
    for (int j=0; j<numColumns; j++)
    {
        cv::Mat matCol = matDif.col(j);
        // detecting which columns have changed
        if (cv::countNonZero(matCol) > 0)
            linesChanged.push_back(listBoardColumns.at(j));
    }        
}

// detect changes in both diagonals
void BoardWatcher::checkChangedDiagonals(cv::Mat& matDif)
{
    // analyse the matDif main diagonal
    cv::Mat matDiagonal = matDif.diag(0);
    // detecting if it has changed
    if (cv::countNonZero(matDiagonal) > 0)
        linesChanged.push_back(listBoardDiagonals.at(0));
    
    // Vertical flip of matDif: the antidiagonal becomes the new diagonal
    cv::Mat matDif2 = matDif.clone();
    matDif.row(0).copyTo(matDif2.row(2));
    matDif.row(2).copyTo(matDif2.row(0));

    // analyse the matDif2 main diagonal (the antidiagonal of matDif)
    cv::Mat matAntiDiagonal = matDif2.diag(0);
    // detecting if it has changed
    if (cv::countNonZero(matAntiDiagonal) > 0)
        linesChanged.push_back(listBoardAntidiagonals.at(0));            
}


void BoardWatcher::updateStableTime()
{
    timeStable++;  // TEMP: iterations instead of time  
}

void BoardWatcher::resetStableTime()
{
    timeStable = 0; // TEMP: iterations instead of time  
}

// Shows the state name
void BoardWatcher::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case BoardWatcher::eSTATE_STABLE:
            stateName = "stable";
            break;
            
        case BoardWatcher::eSTATE_CHANGING:            
            stateName = "changing";
            break;

        case BoardWatcher::eSTATE_LOST:
            stateName = "lost";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}