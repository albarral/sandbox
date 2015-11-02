/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "modules/play/SmartPlayer.h"
#include "learn/GameState.h"
#include "learn/TaskReward.h"
#include "TaskFactory.h"    // temp until task in DB
#include "utils/TaskTree.h"
#include "modules/PurposeWinner.h"

namespace sam 
{
SmartPlayer::SmartPlayer() 
{  
    pPlayerPurpose = new PurposeWinner(5, 10);  // games to learn, games to play
}

SmartPlayer::~SmartPlayer()
{
    if (pPlayerPurpose != 0)
    delete pPlayerPurpose;
}

void SmartPlayer::init(std::string firstPlayerID)
{
    Player::init(firstPlayerID);
    
    LOG4CXX_INFO(logger, "Smart player: load game task ... ");  

    // load attack & defense tasks from memory (DB))
    oAttackTask.setID(1);
    oDefenseTask.setID(2);
    oAttackTask.loadFromMemo2();
    oDefenseTask.loadFromMemo2();

    // if not in DB, create them
    if (oAttackTask.getListGameStates().size() == 0 && oDefenseTask.getListGameStates().size() == 0)
    {
        LOG4CXX_WARN(logger, "Smart player: game task CREATED, NOT YET IN DATABASE");  

        // Built attack task
        TaskFactory::buildTicTacToeTask(oAttackTask);             
        oAttackTask.storeInMemo2();         

        // prepare defense task & strategy
        // Built defense task
        TaskFactory::buildTicTacToeTask(oDefenseTask);               
        oDefenseTask.storeInMemo2();         
    }

    // set rewards for tasks        
    TaskReward::setTaskRewards(oAttackTask, TaskReward::eTASK_T3_ATTACK);
    TaskReward::setTaskRewards(oDefenseTask, TaskReward::eTASK_T3_DEFENSE);

    // prepare strategies
    oAttackStrategy.init(oAttackTask); 
    oDefenseStrategy.init(oDefenseTask);  

    // describe the tasks
    TaskTree::showTask2(oAttackTask);
    TaskTree::showTask2(oDefenseTask);      
    
    int numStates = oAttackTask.getListGameStates().size();
    matQattack = cv::Mat(numStates, numStates, CV_8UC1);     
    matQdefense = cv::Mat(numStates, numStates, CV_8UC1);     
};


void SmartPlayer::chooseCell()
{
    // Chooses an empty cell from the board, marking it with the agent's mark.
    // The selection is done based on learned knowledge (using QLearning).
    cv::Mat matrix = oGameBoard.getMatrix();    
    int* pBestMove;
    
    // select move ...

    // show Q matrices
    TaskTree::getTaskQMatrix(matQattack, oAttackTask);
    TaskTree::getTaskQMatrix(matQdefense, oDefenseTask);
    LOG4CXX_INFO(logger, "\n Qattack:\n" << matQattack);
    LOG4CXX_INFO(logger, "\n Qdefend:\n" << matQdefense);
    
    // set explorative modes
    oAttackStrategy.setExplorativeMode(oPlayerIdentity.isSmartExplorativePlayer());
    oDefenseStrategy.setExplorativeMode(oPlayerIdentity.isSmartExplorativePlayer());

    LOG4CXX_INFO(logger, "ATTACK ... \n");  
    oAttackStrategy.playSmart(matrix, oPlayerIdentity.getMyMark());
    LOG4CXX_INFO(logger, "DEFEND ... \n");  
    oDefenseStrategy.playSmart(matrix, oPlayerIdentity.getMyMark());

    // attack move
    if (oAttackStrategy.getBestReward() >= oDefenseStrategy.getBestReward())
    {
        LOG4CXX_INFO(logger, "ATTACK MOVE");  
        pBestMove = oAttackStrategy.getBestMove();
    }
    // defensive move
    else
    {
        LOG4CXX_INFO(logger, "DEFENSE MOVE");  
        pBestMove = oDefenseStrategy.getBestMove();            
    }
    
    LOG4CXX_INFO(logger, "mark cell " << pBestMove[0] << ", " << pBestMove[1]);  
    // perform move & change turn
    oGameBoard.markCell(oPlayerIdentity.getMyMark(), pBestMove[0], pBestMove[1]);

    LOG4CXX_INFO(logger, "\n " << oGameBoard.getMatrix());
}


void SmartPlayer::endOfGame()
{
    // when a game ends, update the learned knowledge about the task
    oAttackTask.storeQ();
    oDefenseTask.storeQ();
}
}