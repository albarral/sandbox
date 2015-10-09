/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for random values
#include <unistd.h> // for sleep()
#include "log4cxx/ndc.h"

#include "modules/Player.h"
#include "modules/Strategy.h"
#include "modules/LearnStrategy.h"
#include "learn/GameTask.h"
#include "learn/GameState.h"
#include "learn/GameDistance.h"
#include "TaskFactory.h"

namespace sam 
{
log4cxx::LoggerPtr Player::logger(log4cxx::Logger::getLogger("sam.player"));

Player::Player() 
{
    sam::GameDistance oGameDistance;
    bsmart = false;
    bQlearn = false;
    oRewardCalculator.setKAttack(100);
    oRewardCalculator.setKDefend(100);  
    oRewardCalculator.setDMaxVictory(oGameDistance.computeDistance2Victory(0,3));
    oRewardCalculator.setDMaxDefeat(oGameDistance.computeDistance2Defeat(3,0));
}

void Player::init(GameBoard& oBoard, std::string name)
{  
    // the agent is given an identity, which will determine its turn and how its cells are marked
    LOG4CXX_INFO(logger, "Player " << name << " initialized");     
        
    pBoard = &oBoard;    
    ID = name;
    
    if (ID == "SAM")
    {
//        bQlearn = true;
        myMark = GameBoard::eCELL_SAM;
    }
    else if (ID == "TAM")
    {
        bsmart = true;
        myMark = GameBoard::eCELL_TAM;
    }
    else         
        LOG4CXX_ERROR(logger, "ID not accepted. Please set a different ID for this player!");          
    

    //LOG4CXX_INFO(logger, "Player loading game task ...");     
    LOG4CXX_INFO(logger, "Creating game task ... (AS NOT EXISTS YET IN DATABASE!!!)");     
    // TEMPORAL: Till not read from DB the game task will be built directly here.
    TaskFactory::buildTicTacToeTask(oGameTask);
    Player::updateGameTaskRewards(oGameTask, oRewardCalculator);
    oStrategy2.init(oGameTask);    
};

void Player::first()
{    
    // agent starts waiting for its turn
    setState(ePLAYER_WAIT);
    setNextState(ePLAYER_WAIT);    

    log4cxx::NDC::push(ID);   	
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
            if (ID == "SAM")
            {
                if (pBoard->getStatus() == GameBoard::eSTAT_TURN_SAM)               
                    setNextState(ePLAYER_PLAY);
            }
            else if (ID == "TAM")
            {
                if (pBoard->getStatus() == GameBoard::eSTAT_TURN_TAM)
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
    cv::Mat matrix = pBoard->getMatrix();    
    Strategy oStrategy;
    int* pBestMove;
    
    // select move ...
    
    // SMART & LEARNING BASED
    if (bQlearn)
    {
        oStrategy2.playSmart(matrix, myMark);
        
        // attack move
        if (oStrategy2.getBestAttackReward() > oStrategy2.getBestDefenseReward())
            pBestMove = oStrategy2.getBestAttackMove();
        // defensive move
        else
            pBestMove = oStrategy2.getBestDefenseMove();            
    }
    // NO LEARNING    
    else
    {
        // SMART
        if (bsmart)
        {
            if (oStrategy.attack(matrix, myMark) == false)
            {
                oStrategy.attackRandom(matrix, myMark);
            }       
        }
        // RANDOM
        else
            oStrategy.attackRandom(matrix, myMark);
        
        pBestMove = oStrategy.getBestMove();        
    }
    
    // perform move & change turn
    pBoard->markCell(myMark, pBestMove[0], pBestMove[1]);
    pBoard->changeTurn();

    LOG4CXX_INFO(logger, "\n " << pBoard->getMatrix());
}

bool Player::checkBoardOpen()
{
    // Checks the cells of the board to see if the game has finished, whether with a winner or in draw 
    cv::Mat matrix = pBoard->getMatrix();
    Line oLine;
    oLine.setMatrix(matrix);        
    // reset board analysis
    bwinner = false;
    nameWinner = "";
    bemptyCells = false;
        
    // check rows
    for (int i=0; i<matrix.rows; i++)
    {
        // check cells in row
        oLine.checkRow(i, myMark, GameBoard::eCELL_EMPTY); 
        analyseLine(oLine);
    }

    // if no winner, check columns
    if (!bwinner)
    {
        for (int j=0; j<matrix.cols; j++)
        {
            // check cells in column
            oLine.checkColumn(j, myMark, GameBoard::eCELL_EMPTY);        
            analyseLine(oLine);
        }
    }    
    
    // if still no winner, check diagonals
    if (!bwinner)
    {
        for (int k=1; k<=2; k++)
        {
            // check cells in diagonal
            oLine.checkDiagonal(k, myMark, GameBoard::eCELL_EMPTY);        
            analyseLine(oLine);
        }    
    }
    
    // game is still open if there's no winner & there are empty cells
    bool bgameOpen = (!bwinner && bemptyCells);
    
    // if game finished update board status
    if (!bgameOpen)
    {
        // finished with a WINNER (and set winner's name if it's me)
        if (bwinner)
        {
            pBoard->setStatus(GameBoard::eSTAT_FINISHED_WINNER);
            if (!nameWinner.empty())
                pBoard->setWinner(nameWinner);
        }
        //finished with DRAW
        else 
            pBoard->setStatus(GameBoard::eSTAT_FINISHED_DRAW);
    }
    
    return bgameOpen;
}


// checks the observed line to see if there's a winner
void Player::analyseLine(Line& oLine)
{
    // first check if there are empty cells (the usual case)
    if (oLine.getNumEmpties() > 0)
    {
        bemptyCells = true;
    }
    // if whole row is mine, I'm the winner!
    else if (oLine.getNumMines() == 3)
    {
        bwinner = true;
        nameWinner = ID;
    }
    // if whole row is for other player, there's another winner!
    else if (oLine.getNumOthers() == 3)
    {
        bwinner = true;
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


 // sets the rewards of the given GameTask using the specified calculator
void Player::updateGameTaskRewards(GameTask& oGameTask, RewardCalculator& oRewardCalculator)
{        
    std::vector<sam::GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<sam::GameState>::iterator it_end = oGameTask.getListGameStates().end();
    
    while (it_gameState != it_end)
    { 
        GameState& oGameState = *it_gameState;
        int* cell = it_gameState->getCells();
        
        computeStateDistances(oGameState);
        updateStateRewards(oGameState, oRewardCalculator);
    }
}

//calculate the distances and store them
void Player::computeStateDistances(GameState& oGameState)
{
    GameDistance oGameDistance;
    int mines = oGameState.getNumMines();
    int others = oGameState.getNumOthers();
    
    int distanceVictory = oGameDistance.computeDistance2Victory(mines, others);
    oGameState.setDVictory(distanceVictory);
    
    int distanceDefeat = oGameDistance.computeDistance2Defeat(mines, others);
    oGameState.setDDefeat(distanceDefeat);
}

//calculate the rewards and store them
void Player::updateStateRewards(GameState& oGameState, RewardCalculator& oRewardCalculator)
{
    float rewardAttack = oRewardCalculator.computeAttackReward(oRewardCalculator.getKAttack(), oGameState.getDVictory(), oRewardCalculator.getDMaxVictory());
    oGameState.setReward(rewardAttack);
    
    float rewardDefend = oRewardCalculator.computeDefendReward(oRewardCalculator.getKDefend(), oGameState.getDDefeat(), oRewardCalculator.getDMaxDefeat());
    oGameState.setRewardDefense(rewardDefend);
}


}