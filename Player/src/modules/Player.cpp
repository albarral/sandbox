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

Player::Player()
{
    GameBoard oBoard;
    setState(ePLAYER_OFF);
    LOG4CXX_INFO(logger, getState());
    showState();
    
    if(oBoard.getStatus() == 1)
        ID = "SAM";
    else if(oBoard.getStatus() == 2)
        ID = "TAM";
}

void Player::init()
{     
    LOG4CXX_INFO(logger, "Player module initialized");
};

void Player::first()
{    
    setState(ePLAYER_WAIT);
    setNextState(ePLAYER_WAIT);    

    log4cxx::NDC::push("player");   	
    log4cxx::NDC::push("wait");   	
}

void Player::loop()
{
    GameBoard oBoard;
    
    if (updateState())
    {
        LOG4CXX_INFO(logger, oBoard.getStatus());
        oBoard.showStates();
        showState();
    }    
          
    switch (getState())
    {
        case ePLAYER_OFF:            
            // nothing done
            break;
            
        case ePLAYER_WAIT:   
            
            if(ID == "SAM")
            {
                while(oBoard.getStatus() != 1)
                    sleep(1);
                
                setNextState(ePLAYER_PLAY);
            }
            else if(ID == "TAM")
            {
                while(oBoard.getStatus() != 2)
                    sleep(1);
                
                setNextState(ePLAYER_PLAY);
            }           
            break;
            
        case ePLAYER_PLAY:        
            
            if(checkBoard(oBoard.getMatrix()) == false)
            {
                oBoard.showStates();
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
    int randNum = rand() % size;
    std::pair<int, int> selectedCell = listEmptyCells.at(randNum);
    x = selectedCell.first;
    z = selectedCell.second;
    
    if(oBoard.getStatus() == 1)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_SAM;
        oBoard.setMatrix(matrix);
    }
    else if(oBoard.getStatus() == 2)
    {
        matrix.at<int>(x,z) = sam::GameBoard::eCELL_TAM;
        oBoard.setMatrix(matrix);
    }
    
    oBoard.ShowMatrix();
    if(checkBoard(matrix) == false)
        setNextState(ePLAYER_WAIT);
    
    //change turn
    if(oBoard.getStatus() == 1)
        oBoard.setStatus(2);
    else if(oBoard.getStatus() == 2)
        oBoard.setStatus(1);
}

bool Player::checkBoard(cv::Mat matrix)
{
    GameBoard oBoard;
    bool finished = false, winner = false;   
    std::vector<std::pair<int, int>> listEmptyCells;
    
    for(int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.cols; j++)
        {
            if(matrix.at<int>(i,j) == 0)
            {
                listEmptyCells.push_back(std::make_pair(i,j));
            }
        }
    }    
    int size = listEmptyCells.size();
    
    // If there are no empty cells the GameBoard status goes to "finished in draw"
    if(size == 0)
    {
        oBoard.setStatus(3);
        finished = true;
    }
    else
    {   
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
                finished = true;
                winner = true;
            }
        }
    }
            
    if(finished)
    {
        setNextState(ePLAYER_FINISHED);  
        
        if(winner)
        {
            // Put sam as a winner
            if(oBoard.getStatus() == 1)
                oBoard.setStatus(4);
            // Put tam as a winner
            else if(oBoard.getStatus() == 2)
                oBoard.setStatus(5);
        }
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