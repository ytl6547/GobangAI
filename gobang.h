#ifndef GOBANG_H
#define GOBANG_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <stdlib.h>
using namespace std;
class gobang{
    public:
        struct Node{

        };
        gobang();
        ~gobang(){};
        int stepScore(int row, int col);
        bool playerMove(int currPlayer);
        bool AIMove(int currPlayer, int currStep);
        bool isAIPossibleStep(int row, int col);
        void startGame();
        pair<int, int> AICalculate(int currPlayer);
        int lineScore(int num, bool end1Blocked, bool end2Blocked);
        int calculateHelper(int currPlayer, int curr);
        //string toString();
        void printBoard();
        void clearBoard();
        void updateBounds(int row, int col);

    private:
        int board[15][15];
        int rep[2];
        //map<string, int> nextStep;
        int seq;
        int stepsToConsider;
        int upperBound;
        int lowerBound;
        int leftBound;
        int rightBound;
};
#endif