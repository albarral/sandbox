/* 
 * File:   main.cpp
 * Author: ainoa
 *
 * Created on March 26, 2015, 1:09 PM
 */


// Do-While == Repeat-Until

#include <cstdlib>  //for the random values
#include <ctime>
#include <iostream>

//     |1|5|-|
//   |2|3|  |6|
//      |    |
//   |0|4|---|

using namespace std;

const int size = 7;
const double gamma = 0.8;
int initialStates[size] = {0, 1, 2, 3, 4, 5, 6};
int iterations = 5;

int R[size][size] =  {{-1, -1, -1, -1, 0, -1, -1},
                      {-1, -1, -1, 0, -1, 0, -1},
		      {-1, -1, -1, 0, -1, -1, -1},
		      {-1, 0, 0, -1, 0, -1, -1},
		      {0, -1, -1, 0, -1, -1, 100},
		      {-1, 0, -1, -1, -1, -1, 100},
                      {-1, -1, -1, -1, 0, 0, 100}};

int Q[size][size] =  {{0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
		      {0, 0, 0, 0, 0, 0, 0},
		      {0, 0, 0, 0, 0, 0, 0},
		      {0, 0, 0, 0, 0, 0, 0},
		      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0}};
int currentState;


void episode(int initialStates);
void selectAction();
int getRandomValue();
int maxQValue(int state, bool returnIndexOnly);
int formula(int action);


int main() {
    
    int newState;
    
    //Starting at all initial states
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            episode(initialStates[j]);
	}
    }
    
    //Print Q matrix
    cout<< "Matrix Q:"<<endl;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout<< Q[i][j];
            if(j < size- 1)
            {
                cout<< ",";
            }
        }
        cout<<endl;
    }
    cout<<endl;
    
    //Print sequences of states
    cout<< "Sequences of states:"<<endl;
    for(int i = 0; i < size; i++)
    {
        currentState = initialStates[i];
        newState = 0;
        while(currentState < 6)
        {
            newState = maxQValue(currentState, true);
            cout << currentState << ", ";
            currentState = newState;
        }
        cout << "6" << endl;
    }
}

void episode(int initialStates)  //The agent will explore from state to state until it reaches the goal
{
    currentState = initialStates;
    
    while(currentState != 6)
    {
        selectAction();
    }
    
    for(int i = 0; i < size; i++)
    {
        selectAction();
    }
}


void selectAction()
{
    int possibleAction;
    
    possibleAction = getRandomValue();
    if(R[currentState][possibleAction] >= 0)
    {
        Q[currentState][possibleAction] = formula(possibleAction);
        currentState = possibleAction;
    }
    
}


int getRandomValue()
{
    int randNumAction;
    bool valid = false;
    
    do
    {        
        randNumAction = rand() % 7;
        if(R[currentState][randNumAction] >= 0)
        {
            valid = true;
        }
    }while(valid == false);
    
    return randNumAction;
}

int maxQValue(int state, bool returnIndexOnly)
{
// if returnIndexOnly = true, a Q matrix index is returned.
// if returnIndexOnly = false, a Q matrix element is returned.
    
    int winner = 0;
    bool foundNewWinner = false;
    bool done = false;
    
    if(done == false)
    {    
        for(int i = 0; i < size; i++)
        {
            if((i < winner) || (i > winner))
            {
		if(Q[state][i] > Q[state][winner])
                {
                    winner = i;
                    foundNewWinner = true;
                }
            }
	}

	if(foundNewWinner == false)
        {
            done = true;
	}

    }

    if(returnIndexOnly == true)
    {
	return winner;
    }
    
    else
    {
	return Q[state][winner];
    }
    
}

int formula(int action)
{
//  Q(state, action) = R(state, action) + Gamma * Max[Q(next state, all actions)]
    
    return (R[currentState][action] + (gamma * maxQValue(action, false)));
}

