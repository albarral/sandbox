/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "modules/play/SimplePlayer.h"
#include "modules/PurposeTrainer.h"

namespace sam 
{
SimplePlayer::SimplePlayer() 
{    
    pPlayerPurpose = new PurposeTrainer();
}

SimplePlayer::~SimplePlayer()
{
    if (pPlayerPurpose != 0)
        delete pPlayerPurpose;
}

void SimplePlayer::chooseCell()
{
    // Chooses an empty cell from the board, marking it with the agent's mark
    // The selection is done using a prefixed strategy.
    // Otherwise, random selection is made among available cells..
    cv::Mat matrix = oGameBoard.getMatrix();    
    int* pBestMove;
    
    // SIMPLE (use simple Strategy rules)
    if (oPlayerIdentity.isSimplePlayer())
    {
        if (oStrategy.attack(matrix, oPlayerIdentity.getMyMark()) == false)
        {
            oStrategy.attackRandom(matrix, oPlayerIdentity.getMyMark());
        }       
    }
    // RANDOM
    else
        oStrategy.attackRandom(matrix, oPlayerIdentity.getMyMark());

    pBestMove = oStrategy.getBestMove();        
    
    LOG4CXX_INFO(logger, "mark cell " << pBestMove[0] << ", " << pBestMove[1]);  
    // perform move & change turn
    oGameBoard.markCell(oPlayerIdentity.getMyMark(), pBestMove[0], pBestMove[1]);

    LOG4CXX_INFO(logger, "\n " << oGameBoard.getMatrix());
}

void SimplePlayer::endOfGame()
{
    // nothing done
}

}