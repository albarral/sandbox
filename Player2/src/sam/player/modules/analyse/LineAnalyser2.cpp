/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "sam/player/modules/analyse/LineAnalyser2.h"
#include "sam/player/data/PlayerData.h"
#include "sam/player/utils/BoardPlace.h"

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

void LineAnalyser::analyseLine(BoardZone& oZone, cv::Mat& matLine, int playMode)
{
    //LOG4CXX_INFO(logger, "analise " << matLine);     
    lineSize = std::max(matLine.rows, matLine.cols);
    
    // reset moves
    listGameMoves.clear();    
    // reset analysis result 
    resetData();    
    // fast line check 
    checkLine(oZone, matLine, myMark);
    
    // if line open, search best move
    if (result == LineAnalyser::eLINE_OPEN)
    {
        // search attack move
        checkMoves4Attack(playMode);
        // search defense move
        checkMoves4Defense(playMode);                
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
    result = LineAnalyser::eLINE_UNDEFINED;    
}

// checks the line state (open, closed, won or lost)
// open: some empty cells, no winner
// closed: no empty cells, no winner
// won: all cells mine, winner
// lost: all cells other's, looser
void LineAnalyser::checkLine(BoardZone& oZone, cv::Mat& matLine, int myMark)
{
    // default game move
    GameMove oGameMove;
    BoardPlace& oBoardPlace = oGameMove.getBoardPlace();
    oBoardPlace.setZone(oZone);
    
    // analyze line cell by cell, filling the list of moves
    for (int i=0; i<lineSize; i++)
    {
        int res = checkCell(matLine.at<uchar>(i), myMark);
        // update the game line with the cell's check result
        gameLine[i] = res;
        // if empty cell, add new move to the list
        if (res == LineAnalyser::eCELL_EMPTY)
        {
            oBoardPlace.setElement(i);
            listGameMoves.push_back(oGameMove);
        }
    }
        
    // classify the line 
    // empty cells -> open line
    if (listGameMoves.size() > 0)
        result = LineAnalyser::eLINE_OPEN;
    // all cells mine -> winner line
    else if (numMines == lineSize)
        result = LineAnalyser::eLINE_WON;
    // all cells other's -> looser line
    else if (numOthers == lineSize)
        result = LineAnalyser::eLINE_LOST;
    // no empty cells & mixed color -> closed line
    else
        result = LineAnalyser::eLINE_CLOSED;
}


// analyzes the given cell
int LineAnalyser::checkCell(int cellValue, int myMark)
{
    // empty cell (store empty position)
    if (cellValue == emptyMark)            
    {
        numEmpties++;
        return LineAnalyser::eCELL_EMPTY;
    }
    // my cell
    else if (cellValue == myMark)
    {
        numMines++;
        return LineAnalyser::eCELL_MINE;
    }
    // other's cell
    else
    {
        numOthers++;   
        return LineAnalyser::eCELL_OTHER;
    }
}

std::string LineAnalyser::getResultName(int result)
{
    std::string name;
    switch (result)
    {
        case LineAnalyser::eLINE_UNDEFINED:
            name = "undefined";
            break;
        case LineAnalyser::eLINE_OPEN:
            name = "open";
            break;
        case LineAnalyser::eLINE_CLOSED:
            name = "closed";
            break;
        case LineAnalyser::eLINE_WON:
            name = "won";
            break;
        case LineAnalyser::eLINE_LOST:
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