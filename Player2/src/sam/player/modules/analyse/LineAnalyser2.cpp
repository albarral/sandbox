/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/LineAnalyser2.h"
#include "sam/player/data/PlayerData.h"

namespace sam 
{
namespace player
{    
log4cxx::LoggerPtr LineAnalyser::logger(log4cxx::Logger::getLogger("sam.player"));

LineAnalyser::LineAnalyser() 
{
    myMark = -1;       // default
    emptyMark = 0;     // default
    resetData();
}
    
void LineAnalyser::setMarks(int mine, int empty) 
{
    myMark = mine; 
    emptyMark = empty;
    LOG4CXX_INFO(logger, "New marks (mine, empty) = " << mine << ", " << empty);   
};    

void LineAnalyser::analyseLine(cv::Mat& matLine, int playMode)
{
    //LOG4CXX_INFO(logger, "analise " << matLine);     
    lineSize = std::max(matLine.rows, matLine.cols);
    
    // reset analysis result 
    resetData();    
    // fast line check 
    checkLine(matLine, myMark);
    
    // if line open, search best move
    if (result == LineAnalyser::eRESULT_OPEN)
    {
        // search attack move
        searchAttackMove(playMode);
        // search defense move
        searchDefenseMove(playMode);                
    }
    // line not open (closed, winner or looser)
    else
    {
        LOG4CXX_INFO(logger, "line result = " << LineAnalyser::getResultName(result));
    }
}

void LineAnalyser::storeKnowledge()
{
    LOG4CXX_INFO(logger, "store knowledge ... TO DO");         
}

void LineAnalyser::resetData()
{
    numMines = numOthers = numEmpties = 0;
    listEmptyCells.clear();        
    result = LineAnalyser::eRESULT_UNDEFINED;    
    Qattack = Qdefense = -1.0;    
}

// checks the line state (open, closed, won or lost)
// open: some empty cells, no winner
// closed: no empty cells, no winner
// won: all cells mine, winner
// lost: all cells other's, looser
void LineAnalyser::checkLine(cv::Mat& matLine, int myMark)
{
    // reset game line
    gameLine.clear();
    
    // analyze line cell by cell
    for (int i=0; i<lineSize; i++)
    {
        checkCell(i, matLine.at<uchar>(i), myMark);
    }
    
    // classify the line 
    // empty cells -> open line
    if (listEmptyCells.size() > 0)
        result = LineAnalyser::eRESULT_OPEN;
    // all cells mine -> winner line
    else if (numMines == lineSize)
        result = LineAnalyser::eRESULT_WON;
    // all cells other's -> looser line
    else if (numOthers == lineSize)
        result = LineAnalyser::eRESULT_LOST;
    // no empty cells & mixed color -> closed line
    else
        result = LineAnalyser::eRESULT_CLOSED;
}


// analyzes the cell in the given position 
void LineAnalyser::checkCell(int pos, int cellValue, int myMark)
{
    // empty cell (store empty position)
    if (cellValue == emptyMark)            
    {
        numEmpties++;
        gameLine.push_back(LineAnalyser::eMARK_EMPTY);
        listEmptyCells.push_back(pos);
    }
    // my cell
    else if (cellValue == myMark)
    {
        numMines++;
        gameLine.push_back(LineAnalyser::eMARK_MINE);
    }
    // other's cell
    else
    {
        numOthers++;   
        gameLine.push_back(LineAnalyser::eMARK_OTHER);
    }
}

std::string LineAnalyser::getResultName(int result)
{
    std::string name;
    switch (result)
    {
        case LineAnalyser::eRESULT_UNDEFINED:
            name = "undefined";
            break;
        case LineAnalyser::eRESULT_OPEN:
            name = "open";
            break;
        case LineAnalyser::eRESULT_CLOSED:
            name = "closed";
            break;
        case LineAnalyser::eRESULT_WON:
            name = "won";
            break;
        case LineAnalyser::eRESULT_LOST:
            name = "lost";
            break;
        default:
            name = "invalid";
            break;
    }
    return name;    
}

}
}