/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/GameAnalyser.h"
#include "sam/player/modules/analyse/SimpleAnalyser2.h"
#include "sam/player/modules/watch/BoardWatcher.h"
#include "sam/player/data/T3Board.h"
#include "sam/player/PlayerConfig.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr GameAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

GameAnalyser::GameAnalyser() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    requiredStableTime = 0; 
    pGameBoard = 0;
    pGameAction = 0;
    pPlayerData = 0;
    pLineAnalyser = 0;
}

GameAnalyser::~GameAnalyser() 
{
    if (pLineAnalyser != 0)
    {
        delete (pLineAnalyser);
        pLineAnalyser = 0;
    }
}

void GameAnalyser::init(GameBoard& oGameBoard, GameAction& oGameAction, PlayerData& oPlayerData)
{
    pGameBoard = &oGameBoard;
    pGameAction = &oGameAction;
    pPlayerData = &oPlayerData;
    matBoard = pGameBoard->getMatrixClone();
    // change analyzer according to new play mode    
    binitialized = changeLineAnalyser();  
    // read configuration
    PlayerConfig oPlayerConfig;
    requiredStableTime = oPlayerConfig.getRequiredLoops2TrustStability();
    LOG4CXX_INFO(logger, "GameAnalyser initialized");     
};

void GameAnalyser::first()
{    
    log4cxx::NDC::push("Analyser");   	
    pGameAction->reset();	

    // we start in DONE state
    if (binitialized && isConnected())
    {
        LOG4CXX_INFO(logger, "started");  
        setState(GameAnalyser::eSTATE_DONE);    
        setPrevState(GameAnalyser::eSTATE_DONE);    
        showStateName();
        // force full check of the board on first analysis
        bFullCheck = true;        
    }
    // if not initialized or not connected to bus -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized or connected. Going off ... ");  
        Module::off();        
    }
}

void GameAnalyser::bye()
{
    LOG4CXX_INFO(logger, "ended");     
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
            if (isBoardStable())
            {
                // fetch new changed lines & add them to the check list
                fetchBoardData();
                // and -> ANALYSE
                setState(GameAnalyser::eSTATE_ANALYSE);                    
            }            
            break;
            
        case GameAnalyser::eSTATE_ANALYSE:

            // if board still stable 
            if (isBoardStable())
            {
                // do analysis
                doAnalysis();         
                // and update game action with best moves
                updateGameAction();
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
        showStateName();    
        setPrevState(getState());
    }

    // write to bus
    writeBus();
}

void GameAnalyser::senseBus()
{
    // read CI's ...
    // CO_ANALYSER_INHIBIT
    binhibited = pBus->getCOBus().getCO_ANALYSER_INHIBIT().checkRequested();
    // CO_ANALYSER_FULLCHECK
    if (!bFullCheck && pBus->getCOBus().getCO_ANALYSER_FULLCHECK().checkRequested())            
        bFullCheck = true;
    // CO_ANALYSER_NEWPLAYMODE
    if (pBus->getCOBus().getCO_ANALYSER_NEWPLAYMODE().checkRequested())
    {
        // change analyzer according to new play mode
        binitialized = changeLineAnalyser();  
    }
    
    // read SO's ... 
    // SO_WATCHER_STATE
    watcherState = pBus->getSOBus().getSO_WATCHER_STATE().getValue();
    // SO_WATCHER_STABLETIME
    watcherStableTime = pBus->getSOBus().getSO_WATCHER_STABLETIME().getValue(); 
}

void GameAnalyser::writeBus()
{
    // write SO's ...: 
    // SO_ANALYSER_STATE    
    pBus->getSOBus().getSO_ANALYSER_STATE().setValue(getState());
}


// changes the line analyser in concordance with the new play mode
bool GameAnalyser::changeLineAnalyser()
{
    // eliminate previous analyser
    if (pLineAnalyser != 0)
    {
        delete (pLineAnalyser);
        pLineAnalyser = 0;
    }
    
    // create new line analyser according to requested playmode       
    switch (pPlayerData->getPlayMode())
    {
        case PlayerData::eMODE_SIMPLE:
        case PlayerData::eMODE_RANDOM:
            pLineAnalyser = new SimpleAnalyser();
            break;            
    }
    
    if (pLineAnalyser != 0)
    {
        // also update analysed marks
        pLineAnalyser->setMarks(pPlayerData->getMyMark(), pPlayerData->getEmptyMark());
        return true;
    }
    else 
    {
        LOG4CXX_ERROR(logger, "No LineAnalyser created!! Unknown playmode " << pPlayerData->getPlayMode());   
        return false;
    }
}

bool GameAnalyser::isBoardStable()
{
    return (watcherState == BoardWatcher::eSTATE_STABLE && watcherStableTime >= requiredStableTime);
}

void GameAnalyser::fetchBoardData()
{
    // fetch the new board info 
    std::vector<BoardZone> listChangedLines;  
    pGameBoard->fetchInfo(matBoard, listChangedLines);
    // if full check requested, fill check list with all board lines
    if (bFullCheck)
    {
        LOG4CXX_INFO(logger, "full check requested");     
        setCompleteCheckList();        
        bFullCheck = false;
    }
    // otherwise, extend check list with changed lines (append)
    else
        lines2Check.insert(lines2Check.end(), listChangedLines.begin(), listChangedLines.end());

    // confirm its change detection to the the watcher module (CO_WATCHER_ACK)
    pBus->getCOBus().getCO_WATCHER_ACK().request();    
}

void GameAnalyser::doAnalysis()
{
    //LOG4CXX_INFO(logger, "analyse ...");     
    listMoves.clear();
        
    // analyse each of the lines in the check list
    while (!lines2Check.empty())
    {        
        BoardZone& oZone = lines2Check.front();
                
        // extract proper line from board
        cv::Mat matLine = getLineFromBoard(oZone);
        
        // analyse line ...
        LOG4CXX_INFO(logger, "- " << oZone.getID()); //  << matLine);    
        pLineAnalyser->analyseLine(oZone, matLine, pPlayerData->getPlayMode());
        
        // extend list of moves with those from the analysed lane 
        listMoves.insert(listMoves.end(), pLineAnalyser->getListMoves().begin(), pLineAnalyser->getListMoves().end());
        
        // remove this line from check list
        lines2Check.pop_front();
    }
    
    // finally store learned data
    pLineAnalyser->storeKnowledge();
}

 // updates game action with best moves
void GameAnalyser::updateGameAction()
{
    GameMove oAttackMove;
    GameMove oDefenseMove;
    
    // get best attack & defense moves from list moves
    LOG4CXX_INFO(logger, "possible moves ...");
    for (GameMove& oMove: listMoves) 
    {
        LOG4CXX_INFO(logger, oMove.toString());
        if (oMove.getQattack() > oAttackMove.getQattack())
        {
            oAttackMove = oMove;
        }
        if (oMove.getQdefense() > oDefenseMove.getQdefense())
        {
            oDefenseMove = oMove;
        }
    }

    if (listMoves.size() > 0)
    {
        LOG4CXX_INFO(logger, "> best attack: " << oAttackMove.toString());
        LOG4CXX_INFO(logger, "> best defense: " << oDefenseMove.toString());
    }

    // update attack move if this is better
    if (oAttackMove.getQattack() > pGameAction->getAttackMoveReward())
    {
        LOG4CXX_INFO(logger, "new attack action !!!");
        pGameAction->updateAttackInfo(oAttackMove);
    }
    // track best defense
    if (oDefenseMove.getQdefense() > pGameAction->getDefenseMoveReward())
    {
        LOG4CXX_INFO(logger, "new defense action !!!");
        pGameAction->updateDefenseInfo(oDefenseMove);                        
    }        
}

// Extract the proper line data from the board matrix
cv::Mat GameAnalyser::getLineFromBoard(BoardZone& oZone)
{
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

    return matLine;    
}

// force a check of the whole board by putting all lines in the check list
void GameAnalyser::setCompleteCheckList()
{
    // get all lines in a tic-tac-toe board
    T3Board oT3Board;
    std::vector<BoardZone>& listBoardZones = oT3Board.getListZones();

    // all board lines list inserted into check list  (can't copy vector to deque)    
    lines2Check.clear();
    lines2Check.insert(lines2Check.end(), listBoardZones.begin(), listBoardZones.end());
}

// Shows the state name
void GameAnalyser::showStateName()
{
    std::string stateName;
    switch (getState())
    {
        case GameAnalyser::eSTATE_WAIT:
            stateName = "wait";
            break;
            
        case GameAnalyser::eSTATE_ANALYSE:
            stateName = "analyse";
            break;

        case GameAnalyser::eSTATE_DONE:
            stateName = "done";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
//    log4cxx::NDC::pop();
//    log4cxx::NDC::push(stateName);   	
}

}
}