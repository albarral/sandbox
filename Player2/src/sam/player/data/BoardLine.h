#ifndef __SAM_PLAYER_BOARDLINE_H
#define __SAM_PLAYER_BOARDLINE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <string>

namespace sam
{  
namespace player
{     
// This class represents the sensed board line.
// It also has features that result from its analysis.    
class BoardLine 
{  
public:
    // cell positions
    enum eCell
    {
        eCELLS_FIRST, 
        eCELLS_SECOND,
        eCELLS_THIRD,
        eCELLS_DIM
    };
    // line types
    enum eType 
    {
        eTYPE_ROW1,
        eTYPE_ROW2,
        eTYPE_ROW3,
        eTYPE_COL1,  
        eTYPE_COL2,
        eTYPE_COL3,
        eTYPE_DIAG1,
        eTYPE_DIAG2,
        eTYPE_DIM   // dimension of eLine enum
    };
    // result of line analysis
    enum eResult  
    {
        eRESULT_OPEN,        // open line (some empty cell)
        eRESULT_CLOSED,    // closed line (filled line, no winner)
        eRESULT_WON,        // winner line (3 mines)
        eRESULT_LOST,       // lost line (3 other's)
        eRESULT_DIM
    };
    // cell values
    enum eMark  
    {
        eMARK_EMPTY,        // empty cell
        eMARK_MINE,          // cell with my mark
        eMARK_OTHER       // cell with other's mark
    };
    
    static const int INVALID_VALUE = -1;
    
private:
    std::mutex mutex;
    int line[BoardLine::eCELLS_DIM];   // line cells as sensed from board
    int lineType;           // type of line (eLine)
    // data from line analysis ...
    int lineResult;             // result of analyzed line (eResult)
    int bestAttackCell;     // cell position for best attack
    int bestDefenseCell;    // cell position for best defense
    float QbestAttack;      // Q for best attack
    float QbestDefense;     // Q for best defense
    
public:
    BoardLine();
        
    // resets all features resulting from the line analysis
    void resetAnalysisResult();     // mutex protected
    
    // returns a copy of sensed line
    void getLineCopy(int* pLineCopy);   // mutex protected
    // updates a sensed line cell 
    void setLineCell(int pos, int value);   // mutex protected

    int getLineType() {return lineType;};
    void setLineType(int value);
 
    int getLineResult() {return lineResult;};
    void setLineResult(int value);

    int getBestAttackCell() {return bestAttackCell;};
    void setBestAttackCell(int value) {bestAttackCell = value;};
    
    int getBestDefenseCell() {return bestDefenseCell;};
    void setBestDefenseCell(int value) {bestDefenseCell = value;};

    float getBestAttackQ() {return QbestAttack;};
    void setBestAttackQ(float value) {QbestAttack = value;};

    float getBestDefenseQ() {return QbestDefense;};
    void setBestDefenseQ(float value) {QbestDefense = value;};
    
    // return a name for the line result
    std::string toStringLineResult();
};
}
}

#endif

