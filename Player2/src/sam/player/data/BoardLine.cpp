/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/player/data/BoardLine.h"

namespace sam
{    
namespace player
{     
BoardLine::BoardLine() 
{
    // set initial line type & value
    lineType = BoardLine::INVALID_VALUE;
    for (int i=0; i<BoardLine::eCELLS_DIM; i++)
    {
        line[i] = BoardLine::INVALID_VALUE;
    }
    resetAnalysisResult();
 }
 
// resets all features resulting from the line analysis
void BoardLine::resetAnalysisResult()
{
    std::lock_guard<std::mutex> locker(mutex);

    lineResult = BoardLine::INVALID_VALUE;
    bestAttackCell = BoardLine::INVALID_VALUE;
    bestDefenseCell = BoardLine::INVALID_VALUE;
    QbestAttack = 0.0;    
    QbestDefense = 0.0;    
}

void BoardLine::getLineCopy(int* pLineCopy)
{
    std::lock_guard<std::mutex> locker(mutex);
    
    // safety check
    if (pLineCopy == 0)
        return;
    
    for (int i=0; i<BoardLine::eCELLS_DIM; i++)
        pLineCopy[i] = line[i];
}

void BoardLine::setLineCell(int pos, int value)
{
    std::lock_guard<std::mutex> locker(mutex);

    // ignore wrong positions
    if (pos < 0 || pos >=eCELLS_DIM)
        return;
    
    line[pos]=value;
}

void BoardLine::setLineType(int value)
{
    // ignore invalid values
    if (value < 0 || value >=eTYPE_DIM)
        return;
    
    lineType=value;    
}

void BoardLine::setLineResult(int value)
{
    // ignore invalid values
    if (value < 0 || value >=eRESULT_DIM)
        return;
    
    lineResult=value;    
}


// return a name for the line result
std::string BoardLine::toStringLineResult()
{
    std::string result;
    switch (lineResult)
    {
        case eRESULT_OPEN:
            result="open line";
            break;
        case eRESULT_CLOSED:
            result="closed line";
            break;
        case eRESULT_WON:
            result="winner line";
            break;
        case eRESULT_LOST:
            result="looser line";
            break;
    }
    return result;
}

}
}