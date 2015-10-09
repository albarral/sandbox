/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "LearnStrategy.h"
#include "learn/GameTask.h"
#include "UpdateRewards.h"
#include "Learn.h"

namespace sam
{    
log4cxx::LoggerPtr LearnStrategy::logger(log4cxx::Logger::getLogger("sam.player"));

LearnStrategy::LearnStrategy() {}

void LearnStrategy::bestMovement(cv::Mat matrix)
{   
    GameTask oGameTask;
    GameState oGameState;
    Learn oLearnPlayer;
    sam::Transition* winner = 0;
    sam::Transition* winnerAttack = 0;
    sam::Transition* winnerDefend = 0;
    int QmaxA = 0, QmaxD = 0;
    
    //List with all the existent GameStates
    std::vector<sam::GameState>& listGameStates = oGameTask.getListGameStates();
    //Return the list with the GameStates that are in the board game
    std::vector<sam::GameState>& listBoardGameStates = getBoardGameStates(matrix, listGameStates);
    
    std::vector<sam::GameState>::iterator it_gameState = listBoardGameStates.begin();
    std::vector<sam::GameState>::iterator it_end = listBoardGameStates.end();
    while (it_gameState != it_end)
    { 
        std::vector<sam::Transition>& listTransition = it_gameState->getListTransitions();        
        std::vector<sam::Transition>::iterator it_transition = listTransition.begin();
        std::vector<sam::Transition>::iterator it_end = listTransition.end();
        while (it_transition != it_end)
        {          
            int nextState = it_transition->getNextState();
            oGameState = listGameStates.at(nextState);
            
            //Calculate the Q values and search for the one with the highest value
            float QAttack = oLearnPlayer.computeQAttack(oGameState);
            it_transition->setQ(QAttack);  //EL SET HAY QUE HACERLO SOLO DEL FINAL??
            if(QAttack > QmaxA)
            {
                QmaxA = QAttack;
                winnerAttack = &(*it_transition);
            }
            
            float QDefend = oLearnPlayer.computeQDefend(oGameState);
            it_transition->setQDefend(QDefend);  //EL SET HAY QUE HACERLO SOLO DEL FINAL??
            if(QDefend > QmaxD)
            {
                QmaxD = QDefend;
                winnerDefend = &(*it_transition);
            }
            
            //Decide which is the final best move
            if(QmaxA > QmaxD)
                winner = winnerAttack;   
            
            else if(QmaxD > QmaxA)
                winner = winnerDefend;
            
            else winner = winnerAttack;
            //SE NECESITA SABER DONDE SE HA DE COLOCAR EL WINNER...
            
            it_transition++;
        }
        it_gameState++;
    }
    
}

//Serch for each GameState, if it match with a line of the board
//If match, save the GameState in a new vector
std::vector<GameState>& LearnStrategy::getBoardGameStates(cv::Mat matrix, std::vector<sam::GameState>& listGameStates)
{
    UpdateRewards oUpdateRewards;   
    std::vector<sam::GameState> listStatesMatrix;
    int cont = 0;
    
    std::vector<sam::GameState>::iterator it_gameState = listGameStates.begin();
    std::vector<sam::GameState>::iterator it_end = listGameStates.end();
    while (it_gameState != it_end)
    { 
        GameState& oGameState = *it_gameState;
        int* cell = it_gameState->getCells();
        
        oUpdateRewards.computeDistances(oGameState);
        oUpdateRewards.computeRewards(oGameState);
        
        //Check rows
        for (int i=0; i<matrix.rows; i++)
        {
            for (int j=0; j<matrix.cols; j++)
            {
                if(matrix.at<int>(i,j) == cell[j])
                    cont++;
            }
            if(cont == 3)
                listStatesMatrix.push_back(oGameState);
            
            cont = 0;               
        }
        
        //Check cols
        for (int j=0; j<matrix.cols; j++)
        {
            for (int i=0; i<matrix.rows; i++)
            {
                if(matrix.at<int>(i,j) == cell[i])
                    cont++;
            }
            if(cont == 3)
                listStatesMatrix.push_back(oGameState);
            
            cont = 0;               
        }
        
        //Check diagonal (from NW to SE)
        for (int k=0; k<matrix.rows; k++)
        {
            if(matrix.at<int>(k,k) == cell[k])
                cont++;
        }
        if(cont == 3)
            listStatesMatrix.push_back(oGameState);
        
        cont = 0;
        
        //Check diagonal (from NE to SW)
        int topColumn = matrix.cols - 1;
        for (int k=0; k<matrix.rows; k++)
        {
            if(matrix.at<int>(k, topColumn - k) == cell[k])
                cont++;
        }  
        if(cont == 3)
            listStatesMatrix.push_back(oGameState);
        
        cont = 0;
        
        //For the tic tac toe game you can only have 8 GameStates
        if(listStatesMatrix.size() == 8)
            break;
        
        it_gameState++;
    } 
    
    return listStatesMatrix;
}

}