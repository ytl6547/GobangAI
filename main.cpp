#include <iostream>
#include "gobang.h"
using namespace std;
class TicTacToe;
int main(){
    gobang* myGame = new gobang();
    myGame->startGame();
    delete myGame;
    return 0;
}