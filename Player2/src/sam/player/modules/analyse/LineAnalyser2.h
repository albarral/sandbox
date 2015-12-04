#ifndef __SAM_PLAYER_LINEANALYSER_H
#define __SAM_PLAYER_LINEANALYSER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "opencv2/core/core.hpp" //for the matrix

namespace sam 
{
namespace player
{    
// Utility class used for the analysis of a board line.
// It searches the best movements for attack & defense given the line configuration..
// It is a base class for different types of line analysers (smart. simple, etc ...).
class LineAnalyser
{
public:
    // result of line analysis
    enum eResult  
    {
        eRESULT_UNDEFINED,
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

protected:
    static log4cxx::LoggerPtr logger;
    int myMark;         // my mark
    int emptyMark;    // empty mark
    std::vector<int>gameLine;   // analysed line converted to game domain (empty/mine/other)
    int lineSize;
    int numMines;       // number of cells marked as mine
    int numOthers;      // number of cells marked as others'
    int numEmpties;     // number of empty cells
    std::vector<int> listEmptyCells;    // positions of empty cells (if any) in the line
    int result;             // result of line analysis (one of eResult)
    float Qattack;              // attack reward
    int attackElement;        // attack element in zone (cell)  
    float Qdefense;            // defense reward 
    int defenseElement;     // defense element in zone (cell)  

public:
    LineAnalyser();
    
    // set marks for cells
    void setMarks(int mine, int empty);
    // analyses the specified line using the given mark and play mode
    void analyseLine(cv::Mat& matLine, int playMode);
    // updates the stored knowledge about the task (for smart players)
    virtual void storeKnowledge() = 0; 
    // gets name of check result
    static std::string getResultName(int checkResult);
    
    float getAttackQ() {return Qattack;};
    float getDefenseQ() {return Qdefense;};
    int getAttackElement() {return attackElement;};
    int getDefenseElement() {return defenseElement;};
    
private:
    // reset analysis data
    void resetData();
    // fast check of the line to determine if it's open or closed
    void checkLine(cv::Mat& matLine, int myMark);
    // analyzes the cell in the given position 
    void checkCell(int pos, int cellValue, int myMark);
    
protected:    
    void setAttackQ(float value) {Qattack = value;};
    void setDefenseQ(float value) {Qdefense = value;};
    void setAttackElement(int value) {attackElement = value;};
    void setDefenseElement(int value) {defenseElement = value;};
    // searches the best attack move for the present board line
    virtual void searchAttackMove(int playMode) = 0;  
    // searches the best defense move for the present board line
    virtual void searchDefenseMove(int playMode) = 0; 
};

}
}
#endif
