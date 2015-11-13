#ifndef __SAM_PLAYER_LINEANALYSER_H
#define __SAM_PLAYER_LINEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "sam/player/utils/module2.h"
#include "sam/player/data/BoardLine.h"
#include "sam/player/data/PlayerMode.h"

namespace sam 
{
namespace player
{    
// This module monitors and analyzes the sensed board line.
// Whenever it changes an analysis is triggered to deduce the best movements for attack & defense.
// This class works as base class for different types of line analyzers (smart. simple, etc ...).
class LineAnalyser : public Module2
{
public:
    // states of LineAnalyser module
    enum eState
    {
        eSTATE_START,
        eSTATE_ANALYSE,
        eSTATE_DONE
    };

protected:
    static log4cxx::LoggerPtr logger;
    int lineCopy[BoardLine::eCELLS_DIM];   // internal copy of the sensed board line
    int prevLineCopy[BoardLine::eCELLS_DIM];   // internal copy of the sensed board line
    int lineGame[BoardLine::eCELLS_DIM];   // board line conversion to analysis domain (mine, others, empty)
    int numMines;       // number of cells marked as mine
    int numOthers;      // number of cells marked as others'
    int numEmpties;     // number of empty cells
    std::vector<int> listEmptyCells;    // positions of empty cells (if any) in the line
    BoardLine* pBoardLine;      // shared data (sensed board, analysis result) 
    PlayerMode* pPlayerMode;   // shared data (player mode)
    int myMark;         // my mark (obtained from PlayerMode)
    int emptyMark;    // empty mark (obtained from PlayerMode)

public:
    LineAnalyser();
    
    // initializes the module 
    void init (BoardLine& oBoardLine, PlayerMode& oPlayerMode);
        
private:    
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             

    // sense bus
    void senseBus();
    // update bus
    void writeBus();
    // checks if any cell in the board line has changed 
    bool checkLineChanged();
    // stores the internal copy of the board line 
    void storeLineCopy();

    // structural method for ANALYSE state 
    void doAnalysis();    
    // analyzes the sensed line
    void analyseLine();
    // analyzes the cell in the given position 
    void analyseCell(int pos);
    // shows the next state name
    void showStateChange();     
    
//protected:    
//    // selects the best cell in the line for attacking purpose
//    virtual void getBestAttack() = 0;
//    // selects the best cell in the line for defensive purpose
//    virtual void getBestDefense() = 0;
//    // stores the increased knowledge (for smart players)
//    virtual void storeKnowledge() = 0;                
};
}
}
#endif
