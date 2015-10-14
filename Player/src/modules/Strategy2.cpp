/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Strategy2.h"
#include "PlayerActions.h"
#include "data/GameBoard.h"
#include "learn/GameDistance.h"

namespace sam
{    
log4cxx::LoggerPtr Strategy2::logger(log4cxx::Logger::getLogger("sam.player"));

Strategy2::Strategy2() 
{
    benabled = false;
}

void Strategy2::init(GameTask& oGameTask)
{
    pGameTask = &oGameTask;
    benabled = true;
    oLearn.setGamma(0.8);

    LOG4CXX_INFO(logger, "Strategy2 functionality initialized");      
};


// Checks all lines in the board (rows, columns & diagonals) in search of the best attack & defense moves.
void Strategy2::playSmart(cv::Mat& matrix, int myMark)
{    
    Line oLine;
    oLine.setMatrix(matrix);

    // zero rewards before the analysis
    bestAttackReward = bestDefenseReward = 0.0;

    // check rows
    for (int i=0; i<matrix.rows; i++)
    {
        // analyse row & check proper moves in it
        oLine.checkRow(i, myMark, GameBoard::EMPTY_MARK);        
        checkBestMovesInRow(i, oLine);
    }    

    // check columns
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check proper moves in it
        oLine.checkColumn(j, myMark, GameBoard::EMPTY_MARK);        
        checkBestMovesInColumn(j, oLine);
    }    
    
    // check diagonals
    for (int k=1; k<=2; k++)
    {
        // analyse diagonal & check proper moves in it
        oLine.checkDiagonal(k, myMark, GameBoard::EMPTY_MARK);        
        checkBestMovesInDiagonal(k, oLine);
    }    
    
}


// checks if this board's line holds the best attack or defense moves at present
void Strategy2::checkBestMovesInRow(int row, Line& oLine)
{
    float attackReward = 0.0, defenseReward = 0.0;
    Transition* bestAttackTransition = 0;
    Transition* bestDefenseTransition = 0;
    PlayerActions oPlayerActions;

    analyseLine(oLine, bestAttackTransition, bestDefenseTransition);
    
    // track best attack move
    if (bestAttackTransition != 0)
    {
        attackReward = bestAttackTransition->getQ();
        LOG4CXX_INFO(logger, "attackQ: " << attackReward);   
        if (attackReward > bestAttackReward)
        {
            bestAttackReward = attackReward;
            GameState& state1 = pGameTask->getListGameStates().at(bestAttackTransition->getStateID());
            GameState& state2 = pGameTask->getListGameStates().at(bestAttackTransition->getNextState());
            
            // store attack move
            if (oPlayerActions.getActions4Transition(state1, state2) > 0)
            {
                int x, y;
                oPlayerActions.applyAction2Row(row, x, y);
                        
                bestAttackMove[0] = y;   // y stores the row
                bestAttackMove[1] = x;   // x stores the column
            }
        }
    }
    
    // track best defense move
    if (bestDefenseTransition != 0)
    {
        defenseReward = bestDefenseTransition->getQDefend();
        LOG4CXX_INFO(logger, "defendQ: " << defenseReward);  
        if (defenseReward > bestDefenseReward)
        {
            bestDefenseReward = defenseReward;
            GameState& state1 = pGameTask->getListGameStates().at(bestDefenseTransition->getStateID());
            GameState& state2 = pGameTask->getListGameStates().at(bestDefenseTransition->getNextState());
            
            // store attack move
            if (oPlayerActions.getActions4Transition(state1, state2) > 0)
            {
                int x, y;
                oPlayerActions.applyAction2Row(row, x, y);
                        
                bestDefenseMove[0] = y;   // y stores the row
                bestDefenseMove[1] = x;   // x stores the column
            }
        }    
    }    
}

// checks if this board's line holds the best attack or defense moves at present
void Strategy2::checkBestMovesInColumn(int column, Line& oLine)
{
    // TO DO ...
}

// checks if this board's line holds the best attack or defense moves at present
void Strategy2::checkBestMovesInDiagonal(int diag, Line& oLine)
{
// TO DO ...
}


// (CORE OF THE SMART STRATEGY)
// Uses the learned knowledge about the task to obtain the best attack & defense rewards of available moves in this line
void Strategy2::analyseLine(Line& oLine, Transition* bestAttackTransition, Transition* bestDefenseTransition)
{
    GameState* pPresentGameState = 0;
    int* lineCells = oLine.getCells();
    
    // 1. Find the game state that corresponds to the present line        
    std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
    std::vector<sam::GameState>::iterator it_gameState = listGameStates.begin();
    std::vector<sam::GameState>::iterator it_end = listGameStates.end();
    while (it_gameState != it_end)
    {        
        int* gameStateCells = it_gameState->getCells();
        
        if (gameStateCells[0] == lineCells[0] && gameStateCells[1] == lineCells[1] && gameStateCells[2] == lineCells[2])
        {
            pPresentGameState = &(*it_gameState);
            break;
        }
        it_gameState++;
    }    
    
    // 2. When found, get the best attack & defense transitions from this state    
    if (pPresentGameState->getListTransitions().size() > 0)
    {
        // - best attack transition: the one with maximum Qattack value 
        bestAttackTransition = getBestAttackTransition(pPresentGameState->getListTransitions());   
        // - best defense transition: the one with maximum Qdefend value 
        bestDefenseTransition = getBestDefenseTransition(pPresentGameState->getListTransitions());
    }    
}


Transition* Strategy2::getBestAttackTransition(std::vector<sam::Transition>& listTransitions)
{
    sam::Transition* winnerTemporal = 0;
    sam::Transition* winnerAttack = 0;
    std::vector<sam::Transition> listWinners;
    float QAttack = 0, QmaxA = 0;
    int randNumTrans;
    
    std::vector<sam::Transition>::iterator it_transition = listTransitions.begin();
    std::vector<sam::Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {    
        Transition& oTransition = *it_transition;
        std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
        GameState& oNextState = listGameStates.at(oTransition.getNextState()); 
        
        //Calculate the Q values and search for the one with the highest value
        QAttack = oLearn.computeQAttack(oNextState);
        it_transition->setQ(QAttack);
        
        if (QAttack > QmaxA)
        {
            QmaxA = QAttack;
            listWinners.clear();
            listWinners.push_back(oTransition);
            winnerAttack = &oTransition;
        }   
        // if various connections share the maximum confidence, take winner randomly among them
        else if (QAttack == QmaxA)
        {
            listWinners.push_back(oTransition);
            
            randNumTrans = rand() % listWinners.size();
            winnerTemporal = &(listWinners.at(randNumTrans));
            winnerAttack = &(listTransitions.at(winnerTemporal->getID()));
        }
        it_transition++;
    }
    return winnerAttack;
}

Transition* Strategy2::getBestDefenseTransition(std::vector<sam::Transition>& listTransitions)
{
    sam::Transition* winnerTemporal = 0;
    sam::Transition* winnerDefense = 0;
    std::vector<sam::Transition> listWinners;
    float QDefense = 0, QmaxD = 0;
    int randNumTrans;
    
    std::vector<sam::Transition>::iterator it_transition = listTransitions.begin();
    std::vector<sam::Transition>::iterator it_end = listTransitions.end();
    while (it_transition != it_end)
    {    
        Transition& oTransition = *it_transition;
        std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
        GameState& oNextState = listGameStates.at(oTransition.getNextState()); 
        
        //Calculate the Q values and search for the one with the highest value
        QDefense = oLearn.computeQDefend(oNextState);
        it_transition->setQDefend(QDefense);
        
        if (QDefense > QmaxD)
        {
            QmaxD = QDefense;
            listWinners.clear();
            listWinners.push_back(oTransition);
            winnerDefense = &oTransition;
        }   
        // if various connections share the maximum confidence, take winner randomly among them
        else if (QDefense == QmaxD)
        {
            listWinners.push_back(oTransition);
            
            randNumTrans = rand() % listWinners.size();
            winnerTemporal = &(listWinners.at(randNumTrans));
            winnerDefense = &(listTransitions.at(winnerTemporal->getID()));
        }
        it_transition++;
    }
    return winnerDefense;
}


 // sets the rewards of the given GameTask using the specified calculator
void Strategy2::updateGameTaskRewards(GameTask& oGameTask, RewardCalculator& oRewardCalculator)
{        
    std::vector<sam::GameState>::iterator it_gameState = oGameTask.getListGameStates().begin();
    std::vector<sam::GameState>::iterator it_end = oGameTask.getListGameStates().end();
    
    while (it_gameState != it_end)
    { 
        GameState& oGameState = *it_gameState;
        int* cell = it_gameState->getCells(); // ESTO LO QUIERES PARA ALGO???
        
        computeStateDistances(oGameState);
        updateStateRewards(oGameState, oRewardCalculator);
        it_gameState++;
    }
}

//calculate the distances and store them
void Strategy2::computeStateDistances(GameState& oGameState)
{    
    int mines = oGameState.getNumMines();
    int others = oGameState.getNumOthers();
    
    int distanceVictory = GameDistance::computeDistance2Victory(mines, others);
    oGameState.setDVictory(distanceVictory);
    
    int distanceDefeat = GameDistance::computeDistance2Defeat(mines, others);
    oGameState.setDDefeat(distanceDefeat);
}

//calculate the rewards and store them
void Strategy2::updateStateRewards(GameState& oGameState, RewardCalculator& oRewardCalculator)
{
    float rewardAttack = oRewardCalculator.computeAttackReward(oRewardCalculator.getKAttack(), oGameState.getDVictory(), oRewardCalculator.getDMaxVictory());
    oGameState.setReward(rewardAttack);
    
    float rewardDefend = oRewardCalculator.computeDefendReward(oRewardCalculator.getKDefend(), oGameState.getDDefeat(), oRewardCalculator.getDMaxDefeat());
    oGameState.setRewardDefense(rewardDefend);
    LOG4CXX_INFO(logger, "GameState" << oGameState.getID() << "rA: " << rewardAttack <<" rD: " << rewardDefend);
}
}