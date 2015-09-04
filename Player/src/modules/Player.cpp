/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  //for random values
#include <vector>
#include <unistd.h> // for sleep()


#include "log4cxx/ndc.h"
#include "Player.h"
#include "GameManager.h"
#include "Strategy.h"

namespace sam 
{
log4cxx::LoggerPtr Player::logger(log4cxx::Logger::getLogger("sam.player"));

Player::Player() 
{
    bsmart = false;
}

void Player::init(GameBoard& oBoard, std::string name)
{  
    // the agent's is given an identity, which will determine its turn and how its cells are marked
    LOG4CXX_INFO(logger, "Player initialized with ID " << name);     
        
    pBoard = &oBoard;    
    ID = name;
    
    if (ID == "SAM")
    {
        myMark = GameBoard::eCELL_SAM;
    }
    else if (ID == "TAM")
    {
        bsmart = true;
        myMark = GameBoard::eCELL_TAM;
    }
    else         
        LOG4CXX_ERROR(logger, "ID not accepted. Please set a different ID for this player!");             
};

void Player::first()
{    
    // agent starts waiting for its turn
    setState(ePLAYER_WAIT);
    setNextState(ePLAYER_WAIT);    

    log4cxx::NDC::push("player");   	
    log4cxx::NDC::push("wait");    
}

void Player::loop()
{   
    if (updateState())
        showState();
          
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
            // If so, select cell & go back to WAIT state
            // Otherwise, go to FINISHED state 
            if (checkBoard(pBoard->getMatrix()) == false)
            {
                pBoard->showStates();
                chooseCell();
            }
            break;
                    
        case ePLAYER_FINISHED:            
            // nothing done
            break;
    }   // end switch    
    
}

void Player::chooseCell()
{
    // Chooses an empty cell from the board, marking it with the agent's mark
    // If bsmart flag is active the cell selection is done using smart strategies 
    // Otherwise, random selection is made among available cells..
    cv::Mat matrix = pBoard->getMatrix();    
    Strategy oStrategy;
    
    if (bsmart)
    {
        if (oStrategy.attack(matrix, myMark) == false)
        {
            oStrategy.attackRandom(matrix, myMark);
        }       
    }
    else
        oStrategy.attackRandom(matrix, myMark);
    
    pBoard->ShowMatrix();
    if (checkBoard(matrix) == false)
        setNextState(ePLAYER_WAIT);
    
    //change turn
    pBoard->changeTurn();
}

bool Player::checkBoard(cv::Mat matrix)
{
    // Checks the cells of the board to see if the the game has finished, whether with a winner or in draw 
    bool finished = false, winner = false;   
    std::vector<std::pair<int, int>> listEmptyCells;
    
    // a list of empty cells is obtained
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            if (matrix.at<int>(i,j) == GameBoard::eCELL_EMPTY)
            {
                listEmptyCells.push_back(std::make_pair(i,j));
            }
        }
    }    
    int size = listEmptyCells.size();
    
    // If there are no empty cells and no winner the GameBoard status goes to "finished in draw"
    if (size == 0)        
        finished = true;

    for (int i = 0; i<3; i++)
    {        
        if (//Check rows        
        (matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) != GameBoard::eCELL_EMPTY)
        //Check columns
        || (matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) != GameBoard::eCELL_EMPTY)
        //Check diagonals      
        || (matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) != GameBoard::eCELL_EMPTY)     
        || (matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) != GameBoard::eCELL_EMPTY))
        {
            finished = true;
            winner = true;
        }
    }
            
    if (finished)
    {
        setNextState(ePLAYER_FINISHED);  
        
        if (winner)
        {
            // Put sam as a winner
            if (pBoard->getStatus() == GameBoard::eSTAT_TURN_SAM)
                pBoard->setStatus(GameBoard::eSTAT_FINISHED_SAM_WINS);
            // Put tam as a winner
            else if (pBoard->getStatus() == GameBoard::eSTAT_TURN_TAM)
                pBoard->setStatus(GameBoard::eSTAT_FINISHED_TAM_WINS);
        }
        else 
            pBoard->setStatus(GameBoard::eSTAT_FINISHED_DRAW);
        
        pBoard->showStates();
    }    
    return finished;       
}

void Player::showState()
{
    std::string stateName;
    switch (getState())
    {
        case ePLAYER_OFF:            
            stateName = "off";
            break;
        case ePLAYER_WAIT:
            stateName = "wait";
            break;
            
        case ePLAYER_PLAY:
            stateName = "play";
            break;
            
        case ePLAYER_FINISHED:
            stateName = "finished";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(stateName);   	
}

}