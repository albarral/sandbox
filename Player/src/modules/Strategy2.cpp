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
        // analyse column & check proper moves in it
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
    
    // 1. Find the game state that corresponds to the present line    
    
    // - walk the list of GameStates (stored in pGameTask) comparing GameState.cells[] with oLine.cells[]
    // - set pPresentGameState
    
    // 2. When found, get the best attack & defense transitions from this state 
    
    // - best attack transition: the one with maximum Qattack value 
    // (analog to Navigation::getSmartestConnection() method)
    // bestAttackTransition = getBestAttackTransition(pPresentGameState->getListTransitions());
    
    // - best defense transition: the one with maximum Qdefend value 
    // (analog to Navigation::getSmartestConnection() method)
    // bestDefenseTransition = getBestDefenseTransition(pPresentGameState->getListTransitions());
    
    // return best reward values
    attackReward = bestAttackTransition->getQ();    
    defenseReward = bestDefenseTransition->getQDefend();
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