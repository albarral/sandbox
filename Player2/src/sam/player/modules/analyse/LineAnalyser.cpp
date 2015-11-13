/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/LineAnalyser.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr LineAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

LineAnalyser::LineAnalyser() 
{
    //  initial state must be Module2::state_OFF
    pBoardLine = 0;
    pPlayerMode = 0;
}

void LineAnalyser::init(BoardLine& oBoardLine, PlayerMode& oPlayerMode)
{
    LOG4CXX_INFO(logger, "Initialize LineAnalyser ...");     

    pBoardLine = &oBoardLine;
    pPlayerMode = &oPlayerMode;
};

void LineAnalyser::first()
{    
    log4cxx::NDC::push("LineAnalyser");   	
    LOG4CXX_INFO(logger, "first ... ");  

    setNextState(LineAnalyser::eSTATE_START);    
    log4cxx::NDC::push("start");    
}

void LineAnalyser::loop()
{   
    // read bus
    senseBus();
    
    updateState();
          
    switch (getState())
    {
        case LineAnalyser::eSTATE_START:            
            
            // get player marks
            // reset analysis data
            // reset internal copy of line
            // and -> DONE
            myMark = pPlayerMode->getMyMark();         
            emptyMark = pPlayerMode->getEmptyMark(); 
            pBoardLine->resetAnalysisResult();
            for (int i=0; i<BoardLine::eCELLS_DIM; i++)
                prevLineCopy[i] = BoardLine::INVALID_VALUE;
            
            setNextState(eSTATE_DONE);    
            
            break;
            
        case LineAnalyser::eSTATE_DONE:            

            // wait till line changes
            // then -> ANALYSE
            if (checkLineChanged())
                setNextState(LineAnalyser::eSTATE_ANALYSE);                
            
            break;

        case LineAnalyser::eSTATE_ANALYSE:   
                        
            // analyze line
            // store knowledge 
            // and -> DONE
            doAnalysis();
            //storeKnowledge();            
            setNextState(LineAnalyser::eSTATE_DONE);                
            
            break;
    }   // end switch    
    
    if (isStateChanged())
        showStateChange();    

    // write to bus
    writeBus();
}

void LineAnalyser::senseBus()
{
    // TO DO
}

void LineAnalyser::writeBus()
{
    // TO DO    
}

// checks if any cell in the board line has changed 
bool LineAnalyser::checkLineChanged()
{
    bool bchanged = false;
    
    // get updated copy of sensed line
    pBoardLine->getLineCopy(lineCopy);

    // compare sensed line with previous copy (cell by cell)
    for (int i=0; i<BoardLine::eCELLS_DIM; i++)
    {
        if (lineCopy[i] != prevLineCopy[i])
        {
            bchanged = true;
            break;                    
        }
    }    

    // if changed, stores the line copy for later checks
    if (bchanged)
        storeLineCopy();

    return bchanged;
}

// stores the internal copy of the board line 
void LineAnalyser::storeLineCopy()
{
    for (int i=0; i<BoardLine::eCELLS_DIM; i++)
    {
        prevLineCopy[i] = lineCopy[i];
    }        
}

void LineAnalyser::doAnalysis()
{
    // reset analysis result 
    pBoardLine->resetAnalysisResult();

    LOG4CXX_INFO(logger, "doAnalysis: line = " << lineCopy[0] << "," << lineCopy[1] << "," << lineCopy[2]);     

    // analyse line
    analyseLine();

    LOG4CXX_INFO(logger, "doAnalysis: result = " << pBoardLine->toStringLineResult());     
    
    // if line open, search best move
    if (pBoardLine->getLineResult() == BoardLine::eRESULT_OPEN)
    {
        // search attack move
        //getBestAttack();
        // search defense move
        //getBestDefense();        
        
        // TEMP
        int bestMove = listEmptyCells.at(0);
        pBoardLine->setBestAttackCell(bestMove);
        pBoardLine->setBestAttackQ(99.0);

        LOG4CXX_INFO(logger, "doAnalysis: attack move = " << bestMove);     
    }
}

// analyzes the state of the line (open, closed, won or lost)
// open: some empty cells, no winner
// closed: no empty cells, no winner
// won: all cells mine, winner
// lost: all cells other's, looser
void LineAnalyser::analyseLine()
{
    // reset analysis info
    numMines = numOthers = numEmpties = 0;
    listEmptyCells.clear();    

    // analyze cells one by one
    for (int i=0; i<BoardLine::eCELLS_DIM; i++)
    {
        analyseCell(i);
    }
    
    // classify the line 
    // empty cells -> open line
    if (listEmptyCells.size() > 0)
    {
        pBoardLine->setLineResult(BoardLine::eRESULT_OPEN);
    }
    // all cells mine -> winner line
    else if (numMines == BoardLine::eCELLS_DIM)
    {
        pBoardLine->setLineResult(BoardLine::eRESULT_WON);
    }
    // all cells other's -> looser line
    else if (numOthers == BoardLine::eCELLS_DIM)
    {
        pBoardLine->setLineResult(BoardLine::eRESULT_LOST);
    }
    // no empty cells, but mixed color -> closed line
    else
    {
        pBoardLine->setLineResult(BoardLine::eRESULT_CLOSED);
    }    
}

// analyzes the cell in the given position 
void LineAnalyser::analyseCell(int pos)
{
    // empty cell (store empty position)
    if (lineCopy[pos] == emptyMark)            
    {
        numEmpties++;
        listEmptyCells.push_back(pos);
        lineGame[pos] = BoardLine::eMARK_EMPTY;
    }
    // my cell
    else if (lineCopy[pos] == myMark)
    {
        numMines++;
        lineGame[pos] = BoardLine::eMARK_MINE;
    }
    // other's cell
    else
    {
        numOthers++;   
        lineGame[pos] = BoardLine::eMARK_OTHER;
    }
}

    
// Shows the next state name
void LineAnalyser::showStateChange()
{
    std::string nextStateName;
    switch (getNextState())
    {
        case LineAnalyser::eSTATE_START:            
            nextStateName = "start";
            break;
            
        case LineAnalyser::eSTATE_ANALYSE:            
            nextStateName = "analyse";
            break;

        case LineAnalyser::eSTATE_DONE:
            nextStateName = "done";
            break;
    }   // end switch    

    LOG4CXX_INFO(logger, ">> " << nextStateName);
    log4cxx::NDC::pop();
    log4cxx::NDC::push(nextStateName);   	
}

}
}