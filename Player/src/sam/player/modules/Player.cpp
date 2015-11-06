/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp" //for the matrix
#include "log4cxx/ndc.h"

#include "sam/player/modules/Player.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr Player::logger(log4cxx::Logger::getLogger("sam.player"));

Player::Player() 
{
    //  initial state must be Module2::state_OFF
    pPlayerPurpose = 0;
}

void Player::init(std::string firstPlayerID)
{
    // the agent is given an identity, which will determine its turn and how its cells are marked
    LOG4CXX_INFO(logger, "Initialize Player ...");     
    LOG4CXX_INFO(logger, oPlayerIdentity.toString());     
        
    bFirstTurn = (firstPlayerID == oPlayerIdentity.getID());
    oGameFlow.setStatus(GameFlow::eGAME_PLAYING);
};

void Player::first()
{    
    log4cxx::NDC::push(oPlayerIdentity.getID());   	
    LOG4CXX_INFO(logger, "first ... ");  

    pPlayerPurpose->reset();
    setNextState(ePLAYER_READY);    
    log4cxx::NDC::push("ready");    
}

void Player::loop()
{   
    updateState();
          
    switch (getState())
    {
        case ePLAYER_READY:            
            
            // want to play & there's an opponent? start
            setNextState(ePLAYER_START);    
            break;
            
        case ePLAYER_START:            

            // if board not empty -> clear it
            if (checkBoardEmpty())
                doClearBoard();
            // otherwise play or wait (depending on first turn)
            else
            {
                if (bFirstTurn)
                    setNextState(ePLAYER_PLAY);    
                else
                    setNextState(ePLAYER_WAIT);    
                break;                
            }

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

            // on game finished, evolve purpose & go back to ready state
            if (pPlayerPurpose->getGamesPlayed() == 0)
            {
                pPlayerPurpose->evolve();   // TEMP (must evolve always & go to READY)
                endOfGame();
            }            
            break;
    }   // end switch    

    if (isStateChanged())
        showStateChange();    
}

bool Player::checkBoardEmpty()
{
    cv::Mat matrix = oGameBoard.getMatrix();
    // check if all cells are 0
    return false;
}

void Player::doClearBoard()
{
    oGameBoard.reset();                    
    oBoardActuator.writeMove(oGameBoard, oPlayerIdentity.getID(), oGameFlow.getStatus());
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
        case ePLAYER_READY:            
            nextStateName = "ready";
            break;
            
        case ePLAYER_START:            
            nextStateName = "start";
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
}