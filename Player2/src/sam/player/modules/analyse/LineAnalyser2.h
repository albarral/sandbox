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

#include "sam/player/data/GameDefs.h"
#include "sam/player/utils/BoardZone.h"
#include "sam/player/utils/GameMove.h"

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
        eLINE_UNDEFINED,
        eLINE_OPEN,        // open line (some empty cell)
        eLINE_CLOSED,    // closed line (filled line, no winner)
        eLINE_WON,        // winner line (3 mines)
        eLINE_LOST,       // lost line (3 other's)
        eLINE_DIM
    };
    // cell values
    enum eMark  
    {
        eCELL_EMPTY,        // empty cell
        eCELL_MINE,          // cell with my mark
        eCELL_OTHER       // cell with other's mark
    };

protected:
    static log4cxx::LoggerPtr logger;
    int myMark;         // my mark
    int emptyMark;    // empty mark
    int gameLine[GameDefs::eCELL_DIM];   // analysed line converted to game domain (empty/mine/other)
    int lineSize;
    int numMines;       // number of cells marked as mine
    int numOthers;      // number of cells marked as others'
    int numEmpties;     // number of empty cells
    std::vector<GameMove> listGameMoves;
    int result;             // result of line analysis (one of eResult)

public:
    LineAnalyser();
    
    // set marks for cells
    void setMarks(int mine, int empty);
    // analyses the specified line using the given mark and play mode
    void analyseLine(BoardZone& oZone, cv::Mat& matLine, int playMode);
    // updates the stored knowledge about the task (for smart players)
    virtual void storeKnowledge() = 0; 
    // gets name of check result
    static std::string getResultName(int checkResult);
    // gets the list of available moves
    std::vector<GameMove>& getListMoves() {return listGameMoves;};
    
private:
    // reset analysis data
    void resetData();
    // fast check of the line to determine if it's open or closed
    void checkLine(BoardZone& oZone, cv::Mat& matLine, int myMark);
    // analyzes the given cell
    int checkCell(int cellValue, int myMark);
    
protected:    
    // searches the best attack move for the present board line
    virtual void checkMoves4Attack(int playMode) = 0;  
    // searches the best defense move for the present board line
    virtual void checkMoves4Defense(int playMode) = 0; 
};

}
}
#endif
