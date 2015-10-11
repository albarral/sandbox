/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "Strategy2.h"
#include "data/GameBoard.h"

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
        oLine.checkRow(i, myMark, GameBoard::eCELL_EMPTY);        
        checkBestMovesInLine(oLine);
    }    

    // check columns
    for (int j=0; j<matrix.cols; j++)
    {
        // analyse column & check proper moves in it
        oLine.checkColumn(j, myMark, GameBoard::eCELL_EMPTY);        
        checkBestMovesInLine(oLine);
    }    
    
    // check diagonals
    for (int k=1; k<=2; k++)
    {
        // analyse diagonal & check proper moves in it
        oLine.checkDiagonal(k, myMark, GameBoard::eCELL_EMPTY);        
        checkBestMovesInLine(oLine);
    }    
    
}


// checks if this board's line holds the best attack or defense moves at present
void Strategy2::checkBestMovesInLine(Line& oLine)
{
    float attackReward, defenseReward;
    analyseLine(oLine, attackReward, defenseReward);

    // track best attack move
    if (attackReward > bestAttackReward)
    {
        bestAttackReward = attackReward;
        storeAttackMove(oLine);
    }
    // track best defense move
    if (defenseReward > bestDefenseReward)
    {
        bestDefenseReward = defenseReward;
        storeDefenseMove(oLine);
    }    
}

// (CORE OF THE SMART STRATEGY)
// Uses the learned knowledge about the task to obtain the best attack & defense rewards of available moves in this line
void Strategy2::analyseLine(Line& oLine, float& attackReward, float& defenseReward)
{
    sam::Transition* bestAttackTransition = 0;
    sam::Transition* bestDefenseTransition = 0;
    GameState* pPresentGameState = 0;
    int* lineCells = oLine.getCells();
    // 1. Find the game state that corresponds to the present line        
    // - walk the list of GameStates (stored in pGameTask) comparing GameState.cells[] with oLine.cells[]
    std::vector<sam::GameState>& listGameStates = pGameTask->getListGameStates();
    std::vector<sam::GameState>::iterator it_gameState = listGameStates.begin();
    std::vector<sam::GameState>::iterator it_end = listGameStates.end();
    while (it_gameState != it_end)
    {        
        int* gameStateCells = it_gameState->getCells();
        
        if(gameStateCells[0] == lineCells[0] && gameStateCells[1] == lineCells[1] && gameStateCells[2] == lineCells[2])
        {
            pPresentGameState = &(*it_gameState);
            break;
        }
        it_gameState++;
    }    
    // 2. When found, get the best attack & defense transitions from this state    
    // - best attack transition: the one with maximum Qattack value 
    bestAttackTransition = getBestAttackTransition(pPresentGameState->getListTransitions());   
    // - best defense transition: the one with maximum Qdefend value 
    bestDefenseTransition = getBestDefenseTransition(pPresentGameState->getListTransitions());
    
    // return best reward values
    attackReward = bestAttackTransition->getQ();    
    defenseReward = bestDefenseTransition->getQDefend();
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
        float QAttack = oLearn.computeQAttack(oNextState);
        it_transition->setQ(QAttack);
        
        if(QAttack > QmaxA)
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
        float QDefense = oLearn.computeQDefend(oNextState);
        it_transition->setQDefend(QDefense);
        
        if(QDefense > QmaxD)
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

// stores one of the line's available moves as best attack move (SHOULD BE DONE FROM NEXT STATE'S INFO)    
void Strategy2::storeAttackMove(Line& oLine)
{
    // simply take the first option (if any)
    if (oLine.getListEmptyCells().size() != 0)
    {
        cv::Point cell = oLine.getListEmptyCells().at(0);
        bestAttackMove[0] = cell.x;   // x stores the row
        bestAttackMove[1] = cell.y;   // y stores the column
    }    
}


// stores one of the line's available moves as best attack move (SHOULD BE DONE FROM NEXT STATE'S INFO)    
void Strategy2::storeDefenseMove(Line& oLine)
{
    // simply take the first option (if any)
    if (oLine.getListEmptyCells().size() != 0)
    {
        cv::Point cell = oLine.getListEmptyCells().at(0);
        bestDefenseMove[0] = cell.x;   // x stores the row
        bestDefenseMove[1] = cell.y;   // y stores the column
    }    
}
}