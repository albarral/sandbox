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
#include "data/GameBoard.h"

using namespace log4cxx;

namespace sam 
{
LoggerPtr Player::logger(Logger::getLogger("sam.player"));

Player::Player(){}

void Player::init()
{
    LOG4CXX_INFO(logger, "Player module initialized");      
};

void Player::first()
{    
    setState(eSTATE_WAIT);
    setNextState(eSTATE_WAIT);    

    log4cxx::NDC::push("player");   	
    log4cxx::NDC::push("wait");   	
}

void Player::loop()
{
    GameManager oGameManager;
    GameManager oBoard;
    
    if (updateState())
        showState();
          
    switch (getState())
    {
        case eSTATE_WAIT:   
            
            // while(oBoard.getStatus != tuTurno)
                sleep(1);
            setNextState(eSTATE_PLAY);
            break;
            
        case eSTATE_PLAY:        
            
            if (oGameManager.isGameOver() == false)
                chooseCell();               
            break;
                    
        case eSTATE_WINNER:            
            // nothing done
            break;
    }   // end switch    
    
}

void Player::chooseCell()
{
    GameBoard oBoard;
    cv::Mat matrix = oBoard.getMatrix();
    std::vector<std::pair<int, int>> listEmptyCells;
    int i, j, x, z;
    
    for(i = 0; i < matrix.rows; i++)
    {
        for(j = 0; j < matrix.cols; j++)
        {
            if(matrix.at<int>(i,j) == 0)
            {
                listEmptyCells.push_back(std::make_pair(i,j));
            }
        }
    }
    
    int size = listEmptyCells.size();
    
    if(size == 0)
        oBoard.eSTAT_FINISHED_DRAW;  //No se si se puede asignar así
    else
    {
        int randNum = rand() % size;
        std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
        x = selectedCell.first;
        z = selectedCell.second;
    }
    
    if(sam::GameBoard::eSTAT_TURN_SAM)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_SAM;
    }
    else if(sam::GameBoard::eSTAT_TURN_TAM)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_TAM;
    }
    
    oBoard.ShowMatrix();
    isWinner(matrix);
}

void Player::isWinner(cv::Mat matrix)
{
    bool winner = false;
    for(int i = 0; i<3; i++)
    {        
        if(//Check rows        
        (matrix.at<int>(i,0) == matrix.at<int>(i,1) && matrix.at<int>(i,0) == matrix.at<int>(i,2) && matrix.at<int>(i,0) != 0)
        //Check columns
        || (matrix.at<int>(0,i) == matrix.at<int>(1,i) && matrix.at<int>(0,i) == matrix.at<int>(2,i) && matrix.at<int>(0,i) != 0)
        //Check diagonals      
        || (matrix.at<int>(0,0) == matrix.at<int>(1,1) && matrix.at<int>(0,0) == matrix.at<int>(2,2) && matrix.at<int>(0,0) != 0)     
        || (matrix.at<int>(2,0) == matrix.at<int>(1,1) && matrix.at<int>(2,0) == matrix.at<int>(0,2) && matrix.at<int>(2,0) != 0))
        {
            winner = true;
        }
    }
            
    if(winner == true)
    {
        setNextState(eSTATE_WINNER);        
    }  
    else setNextState(eSTATE_WAIT);
           
}

void Player::showState()
{
    std::string stateName;
    switch (getState())
    {
        case eSTATE_WAIT:
            stateName = "wait";
            break;
            
        case eSTATE_PLAY:
            stateName = "play";
            break;
            
        case eSTATE_WINNER:
            stateName = "winner";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << stateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(stateName);   	
}

}