/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for random values
#include <unistd.h> // for sleep()
#include "log4cxx/ndc.h"

#include "modules/Player.h"
#include "modules/Strategy.h"
#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "learn/GameDistance.h"
#include "TaskFactory.h"

namespace sam 
{
log4cxx::LoggerPtr Player::logger(log4cxx::Logger::getLogger("sam.player"));

Player::Player() 
{
    oRewardCalculator.setKAttack(100);
    oRewardCalculator.setKDefend(100);  
    oRewardCalculator.setDMaxVictory(GameDistance::computeDistance2Victory(0,3));
    oRewardCalculator.setDMaxDefeat(GameDistance::computeDistance2Defeat(3,0));
}

void Player::init(GameBoard& oGameBoard, GameFlow& oGameFlow)
{  
    // the agent is given an identity, which will determine its turn and how its cells are marked
    LOG4CXX_INFO(logger, "Initialize Player ...");     
    LOG4CXX_INFO(logger, oPlayerIdentity.toString());     
        
    pGameBoard = &oGameBoard;    
    pGameFlow = &oGameFlow;    

    if (oPlayerIdentity.isSmartPlayer())
    {
        LOG4CXX_INFO(logger, "Smart player: load game task ... (CREATE IT HERE AS NOT EXISTS YET IN DATABASE!!!)");     
        // TEMPORAL: Till not read from DB the game task will be built directly here.
        TaskFactory::buildTicTacToeTask(oGameTask);
        
        // set rewards of task states using my attack & defense sensibilty
        Strategy2::updateGameTaskRewards(oGameTask, oRewardCalculator);
        oStrategy2.init(oGameTask);            
    }
};

void Player::first()
{    
    // agent starts waiting for its turn
    setState(ePLAYER_WAIT);
    setNextState(ePLAYER_WAIT);    

    log4cxx::NDC::push(oPlayerIdentity.getID());   	
    log4cxx::NDC::push("wait");    
}

void Player::loop()
{   
    updateState();
          
    switch (getState())
    {
        case ePLAYER_OFF:            
            // nothing done
            break;
            
        case ePLAYER_WAIT:   
            
            // check if agent's turn has arrived 
            // if so, go to PLAY state 
            if (oPlayerIdentity.getID() == pGameFlow->getPlayerWithTurn()->getID())
            {
                setNextState(ePLAYER_PLAY);
            }
            break;
            
        case ePLAYER_PLAY:        
            
            // check if game still open
            // If so, make move
            // check again & go back to WAIT state or to FINISHED depending on the result
            if (checkBoardOpen())
            {
                chooseCell();          
                
                if (checkBoardOpen())
                    setNextState(ePLAYER_WAIT);    
                else
                    setNextState(ePLAYER_FINISHED);                    
            }
            // Otherwise, go to FINISHED state 
            else 
                setNextState(ePLAYER_FINISHED);
                
            break;
                    
        case ePLAYER_FINISHED:             
            // nothing done
            break;
    }   // end switch    

    if (isStateChanged())
        showStateChange();    
}

void Player::chooseCell()
{
    // Chooses an empty cell from the board, marking it with the agent's mark
    // If bQlearn flag is active the cell selection is done using QLearning
    // If bsmart flag is active the cell selection is done using smart strategies 
    // Otherwise, random selection is made among available cells..
    cv::Mat matrix = pGameBoard->getMatrix();    
    Strategy oStrategy;
    int* pBestMove;
    
    // select move ...
    
    // SMART (LEARNING BASED)
    if (oPlayerIdentity.isSmartPlayer())
    {
        oStrategy2.playSmart(matrix, oPlayerIdentity.getMyMark());
        
        // attack move
        if (oStrategy2.getBestAttackReward() >= oStrategy2.getBestDefenseReward())
            pBestMove = oStrategy2.getBestAttackMove();
        // defensive move
        else
            pBestMove = oStrategy2.getBestDefenseMove();            
    }
    // NO LEARNING    
    else
    {
        // SIMPLE (use simple Strategy rules)
        if (oPlayerIdentity.isSimplePlayer())
        {
            if (oStrategy.attack(matrix, oPlayerIdentity.getMyMark()) == false)
            {
                oStrategy.attackRandom(matrix, oPlayerIdentity.getMyMark());
            }       
        }
        // RANDOM
        else
            oStrategy.attackRandom(matrix, oPlayerIdentity.getMyMark());
        
        pBestMove = oStrategy.getBestMove();        
    }
    
    // perform move & change turn
    pGameBoard->markCell(oPlayerIdentity.getMyMark(), pBestMove[0], pBestMove[1]);
    pGameFlow->changeTurn();

    LOG4CXX_INFO(logger, "\n " << pGameBoard->getMatrix());
}

bool Player::checkBoardOpen()
{
    // Checks the cells of the board to see if the game has finished, whether with a winner or in draw 
    cv::Mat matrix = pGameBoard->getMatrix();
    Line oLine;
    oLine.setMatrix(matrix);        
    // reset board analysis
    bemptyCells = false;
        
    if (pGameFlow->isGameOver())
        return false;
 
    // if game open, check rows
    for (int i=0; i<matrix.rows; i++)
    {
        // check cells in row
        oLine.checkRow(i, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK); 
        analyseLine(oLine);
    }

    if (pGameFlow->isGameOver())
        return false;

    // if game still open, check columns
    for (int j=0; j<matrix.cols; j++)
    {
        // check cells in column
        oLine.checkColumn(j, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK);        
        analyseLine(oLine);
    }
    
    if (pGameFlow->isGameOver())
        return false;

    // if game still open, check diagonals
    for (int k=1; k<=2; k++)
    {
        // check cells in diagonal
        oLine.checkDiagonal(k, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK);        
        analyseLine(oLine);
    }    

    if (pGameFlow->isGameOver())
        return false;
    
    // if game not over, but no empty cells -> game over in draw
    if (!bemptyCells)
        pGameFlow->setStatus(GameFlow::eGAME_OVER_DRAW);
        
    // game is open if not over
    return (pGameFlow->isGameOver() == false);
}


void Player::analyseLine(Line& oLine)
{
    // first check if there are empty cells (the usual case)
    if (oLine.getNumEmpties() > 0)
    {
        bemptyCells = true;
    }
    // if whole line is mine, I'M THE WINNER!
    else if (oLine.getNumMines() == GameBoard::LINE_SIZE)
    {
        pGameFlow->setStatus(GameFlow::eGAME_OVER_WINNER);
        pGameFlow->setWinner(oPlayerIdentity);
    }
    // if whole row is for other player, there's another winner!
    else if (oLine.getNumOthers() == GameBoard::LINE_SIZE)
    {
        pGameFlow->setStatus(GameFlow::eGAME_OVER_WINNER);
    }
}


bool Player::isPlayerFinished()
{
    return (getState() == ePLAYER_FINISHED);
}

// Shows the next state name
void Player::showStateChange()
{
    std::string nextStateName;
    switch (getNextState())
    {
        case ePLAYER_OFF:            
            nextStateName = "off";
            break;
            
        case ePLAYER_WAIT:
            nextStateName = "wait";
            break;
            
        case ePLAYER_PLAY:
            nextStateName = "play";
            break;
            
        case ePLAYER_FINISHED:
            nextStateName = "finished";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << nextStateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(nextStateName);   	
}





}