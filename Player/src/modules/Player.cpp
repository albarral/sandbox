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
#include "learn/TaskReward.h"
#include "TaskFactory.h"
#include "utils/TaskTree.h"

namespace sam 
{
log4cxx::LoggerPtr Player::logger(log4cxx::Logger::getLogger("sam.player"));

Player::Player() 
{
    //  initial state must be Module2::state_OFF
}

void Player::init(std::string firstPlayerID)
{
    stored = false;
    // the agent is given an identity, which will determine its turn and how its cells are marked
    LOG4CXX_INFO(logger, "Initialize Player ...");     
    LOG4CXX_INFO(logger, oPlayerIdentity.toString());     
        
    bFirstTurn = (firstPlayerID == oPlayerIdentity.getID());
    oGameFlow.setStatus(GameFlow::eGAME_PLAYING);

    if (oPlayerIdentity.isSmartPlayer())
    {
        LOG4CXX_INFO(logger, "Smart player: load game task ... ");  
        
        // load attack & defense tasks from memory (DB))
        oAttackTask.setID(1);
        oDefenseTask.setID(2);
        oAttackTask.loadFromMemo2();
        oDefenseTask.loadFromMemo2();
        
        // if not in DB, create them
        if (oAttackTask.getListGameStates().size() == 0 && oDefenseTask.getListGameStates().size() == 0)
        {
            LOG4CXX_WARN(logger, "Smart player: game task CREATED, NOT YET IN DATABASE");  

            // Built attack task
            TaskFactory::buildTicTacToeTask(oAttackTask);             
            oAttackTask.storeInMemo2();         

            // prepare defense task & strategy
            // Built defense task
            TaskFactory::buildTicTacToeTask(oDefenseTask);               
            oDefenseTask.storeInMemo2();         
        }
        
        // set rewards for tasks        
        TaskReward::setTaskRewards(oAttackTask, TaskReward::eTASK_T3_ATTACK);
        TaskReward::setTaskRewards(oDefenseTask, TaskReward::eTASK_T3_DEFENSE);

        // prepare strategies
        oAttackStrategy.init(oAttackTask); 
        oDefenseStrategy.init(oDefenseTask);  

        // describe the tasks
        TaskTree::showTask2(oAttackTask);
        TaskTree::showTask2(oDefenseTask);      
    }
};

void Player::first()
{    
    log4cxx::NDC::push(oPlayerIdentity.getID());   	
    // agent starts waiting for its turn
    if (bFirstTurn)
    {
        setState(ePLAYER_PLAY);    
        setNextState(ePLAYER_PLAY);    
        log4cxx::NDC::push("play");    
    }
    else
    {
        setState(ePLAYER_WAIT);    
        setNextState(ePLAYER_WAIT);    
        log4cxx::NDC::push("wait");    
    }

    LOG4CXX_INFO(logger, "first ... ");  
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
            oBoardSensor.senseBoard(oGameBoard);            

            // if last player is not me, it's my turn
            if (oPlayerIdentity.getID() != oBoardSensor.getLastMovePlayer())            
            {
                setNextState(ePLAYER_PLAY);
            }
            break;
            
        case ePLAYER_PLAY:        
            
            // check if game still open
            // If so, make move
            // check again & go back to WAIT state or to FINISHED depending on the result
            oBoardSensor.senseBoard(oGameBoard);   
            oGameFlow.setStatus(oBoardSensor.getLastMoveStatus());

            if (checkBoardOpen())
            {
                chooseCell();          
                
                if (checkBoardOpen())
                    setNextState(ePLAYER_WAIT);    
                else
                    setNextState(ePLAYER_FINISHED); 
                
                // perform move in TAB_BOARD
                oBoardActuator.writeMove(oGameBoard, oPlayerIdentity.getID(), oGameFlow.getStatus());
            }
            // Otherwise, go to FINISHED state 
            else 
            {
                setNextState(ePLAYER_FINISHED);
                oBoardActuator.updateLastMoveStatus(oGameFlow.getStatus());
            }
                        
            break;
                    
        case ePLAYER_FINISHED:              

            // store the learned task 
            if (oPlayerIdentity.isSmartPlayer() && !stored)
            {
                oAttackTask.storeQ();
                oDefenseTask.storeQ();
                stored = true;
            }
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
    cv::Mat matrix = oGameBoard.getMatrix();    
    Strategy oStrategy;
    int* pBestMove;
    
    // select move ...
    
    // SMART (LEARNING BASED)
    if (oPlayerIdentity.isSmartPlayer())
    {
        // set explorative modes
        oAttackStrategy.setExplorativeMode(oPlayerIdentity.isSmartExplorativePlayer());
        oDefenseStrategy.setExplorativeMode(oPlayerIdentity.isSmartExplorativePlayer());
        
        LOG4CXX_INFO(logger, "ATTACK ... \n");  
        oAttackStrategy.playSmart(matrix, oPlayerIdentity.getMyMark());
        LOG4CXX_INFO(logger, "DEFEND ... \n");  
        oDefenseStrategy.playSmart(matrix, oPlayerIdentity.getMyMark());
        
        // attack move
        if (oAttackStrategy.getBestReward() >= oDefenseStrategy.getBestReward())
        {
            LOG4CXX_INFO(logger, "ATTACK MOVE");  
            pBestMove = oAttackStrategy.getBestMove();
        }
        // defensive move
        else
        {
            LOG4CXX_INFO(logger, "DEFENSE MOVE");  
            pBestMove = oDefenseStrategy.getBestMove();            
        }
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
    
    LOG4CXX_INFO(logger, "mark cell " << pBestMove[0] << ", " << pBestMove[1]);  
    // perform move & change turn
    oGameBoard.markCell(oPlayerIdentity.getMyMark(), pBestMove[0], pBestMove[1]);

    LOG4CXX_INFO(logger, "\n " << oGameBoard.getMatrix());
}

bool Player::checkBoardOpen()
{
    // Checks the cells of the board to see if the game has finished, whether with a winner or in draw 
    cv::Mat matrix = oGameBoard.getMatrix();
    Line oLine;
    oLine.setMatrix(matrix);        
    // reset board analysis
    bemptyCells = false;
        
    if (oGameFlow.isGameOver())
        return false;
 
    // if game open, check rows
    for (int i=0; i<matrix.rows; i++)
    {
        // check cells in row
        oLine.checkRow(i, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK); 
        analyseLine(oLine);
    }

    if (oGameFlow.isGameOver())
        return false;

    // if game still open, check columns
    for (int j=0; j<matrix.cols; j++)
    {
        // check cells in column
        oLine.checkColumn(j, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK);        
        analyseLine(oLine);
    }
    
    if (oGameFlow.isGameOver())
        return false;

    // if game still open, check diagonals
    for (int k=1; k<=2; k++)
    {
        // check cells in diagonal
        oLine.checkDiagonal(k, oPlayerIdentity.getMyMark(), GameBoard::EMPTY_MARK);        
        analyseLine(oLine);
    }    

    if (oGameFlow.isGameOver())
        return false;
    
    // if game not over, but no empty cells -> game over in draw
    if (!bemptyCells)
        oGameFlow.setStatus(GameFlow::eGAME_OVER_DRAW);
        
    // game is open if not over
    return (!oGameFlow.isGameOver());
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
        oGameFlow.setStatus(GameFlow::eGAME_OVER_WINNER);
        oGameFlow.setWinner(oPlayerIdentity);
    }
    // if whole row is for other player, there's another winner!
    else if (oLine.getNumOthers() == GameBoard::LINE_SIZE)
    {
        oGameFlow.setStatus(GameFlow::eGAME_OVER_WINNER);
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