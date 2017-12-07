#include "gobang.h"
gobang::gobang(){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            board[i][j]=0;
        }
    }
    rep[0]=-1;
    rep[1]=1;
    stepsToConsider = 5;
    upperBound = 7;
    lowerBound = 7;
    leftBound = 7;
    rightBound = 7;
}
int gobang::lineScore(int num, bool end1Blocked, bool end2Blocked){
    if(num>=5){
        return 100000;
    }
    else if(end1Blocked&&end2Blocked){
        return 0;
    }
    else if(num==4){
        if(!end1Blocked&&!end2Blocked){
            return 10000;
        }
        else if(!(end1Blocked&&end2Blocked)){
            return 2000;
        }
    }
    else if(num==3){
        if(!end1Blocked&&!end2Blocked){
            return 2000;
        }
        else if(!(end1Blocked&&end2Blocked)){
            return 100;
        }
    }
    else if(num==2){
        if(!end1Blocked&&!end2Blocked){
            return 100;
        }
        else if(!(end1Blocked&&end2Blocked)){
            return 10;
        }
    }
    else if(num==1){
        if(!end1Blocked&&!end2Blocked){
            return 10;
        }
        else if(!(end1Blocked&&end2Blocked)){
            return 5;
        }
    }
}
int gobang::stepScore(int row, int col){
    int player=board[row][col];
    int numAdjacent=1;
    int currRow;
    int currCol;
    int score = 0;
    bool end1Blocked;
    bool end2Blocked;
    //check win in row
    currCol=col+1;
    while(currCol<=14 && board[row][currCol]==player){
        numAdjacent++;
        currCol++;
    }
    if(currCol>14||board[row][currCol]*player==-1){
        end1Blocked=true;
    }
    else{
        end1Blocked=false;
    }
    currCol=col-1;
    while(currCol>=0 && board[row][currCol]==player){
        numAdjacent++;
        currCol--;
    }
    if(currCol<0||board[row][currCol]*player==-1){
        end2Blocked=true;
    }
    else{
        end2Blocked=false;
    }
    score += lineScore(numAdjacent, end1Blocked, end2Blocked);
    numAdjacent=1;

    //check win in col
    currRow=row+1;
    while(currRow<=14 && board[currRow][col]==player){
        numAdjacent++;
        currRow++;
    }
    if(currRow>14||board[currRow][col]*player==-1){
        end1Blocked=true;
    }
    else{
        end1Blocked=false;
    }
    currRow=row-1;
    while(currRow>=0 && board[currRow][col]==player){
        numAdjacent++;
        currRow--;
    }
    if(currRow<0||board[currRow][col]*player==-1){
        end2Blocked=true;
    }
    else{
        end2Blocked=false;
    }
    score += lineScore(numAdjacent, end1Blocked, end2Blocked);
    numAdjacent=1;

    //check win in a tilted direction
    currRow = row+1;
    currCol = col+1;
    while((currRow<=14&&currCol<=14) && board[currRow][currCol]==player){
        numAdjacent++;
        currRow++;
        currCol++;
    }
    if(currRow>14||currCol>14||board[currRow][currCol]*player==-1){
        end1Blocked=true;
    }
    else{
        end1Blocked=false;
    }
    currRow = row-1;
    currCol = col-1;
    while((currRow>=0&&currCol>=0) && board[currRow][currCol]==player){
        numAdjacent++;
        currRow--;
        currCol--;
    }
    if(currRow<0||currCol<0||board[currRow][currCol]*player==-1){
        end2Blocked=true;
    }
    else{
        end2Blocked=false;
    }
    score += lineScore(numAdjacent, end1Blocked, end2Blocked);
    numAdjacent=1;

    //check win in another tilted direction
    currRow = row+1;
    currCol = col-1;
    while((currRow<=14&&currCol>=0) && board[currRow][currCol]==player){
        numAdjacent++;
        currRow++;
        currCol--;
    }
    if(currRow>14||currCol<0||board[currRow][currCol]*player==-1){
        end1Blocked=true;
    }
    else{
        end1Blocked=false;
    }
    currRow = row-1;
    currCol = col+1;
    while((currRow>=0&&currCol<=14) && board[currRow][currCol]==player){
        numAdjacent++;
        currRow--;
        currCol++;
    }
    if(currRow<0||currCol>14||board[currRow][currCol]*player==-1){
        end2Blocked=true;
    }
    else{
        end2Blocked=false;
    }
    score += lineScore(numAdjacent, end1Blocked, end2Blocked);
    numAdjacent=1;

    return player*(score+14-abs(row-7)-abs(col-7));
}
void gobang::updateBounds(int row, int col){
    if(row<=upperBound){
        upperBound = row;
        if(upperBound>=1){
            upperBound--;
        }
    }
    if(row>=lowerBound){
        lowerBound = row;
        if(lowerBound<=13){
            lowerBound++;
        }
    }
    if(col<=leftBound){
        leftBound = col;
        if(leftBound>=1){
            leftBound--;
        }
    }
    if(col>=rightBound){
        rightBound = col;
        if(rightBound<=13){
            rightBound++;
        }
    }
}
bool gobang::playerMove(int currPlayer){
    cout<<"Your turn, type in row and col of a spot: ";
    int row, col;
    cin>>row>>col;
    while(board[row][col]!=0){
        cout<<"invalid input"<<endl;
        cout<<"choose your spot again: ";
        cin>>row>>col;
    }
    board[row][col]=currPlayer;
    updateBounds(row, col);
    cout<<upperBound<<" "<<lowerBound<<" "<<leftBound<<" "<<rightBound<<endl;
    if(stepScore(row, col)*currPlayer>=100000){
        return true;
    }
    else return false;
}
bool gobang::isAIPossibleStep(int row, int col){
    if(board[row][col]!=0){
        return false;
    }
    for(int i=row-1; i<=row+1; i++){
        if(i<0){
            continue;
        }
        if(i>14){
            break;
        }
        for(int j=col-1; j<=col+1; j++){
            if(j<0){
                continue;
            }
            if(j>14){
                break;
            }
            if(board[i][j]!=0){
                return true;
            }
        }
    }
    return false;
}
int gobang::calculateHelper(int currPlayer, int curr){
    //cout<<currPlayer<<" "<<curr<<endl;
    if(curr==stepsToConsider+1){
        return 0;
    }
    int best=-2147483648;
    int bestCurrScore = -1;
    bool existPossibleStep=false;
    int upper = upperBound;
    int lower = lowerBound;
    int left = leftBound;
    int right = rightBound;
    // int row, col;
    for(int i=upper; i<=lower; i++){
        for(int j=left; j<=right; j++){
            if(isAIPossibleStep(i, j)){
                existPossibleStep=true;
                board[i][j]=currPlayer;
                int currScore = stepScore(i, j);
                if(currPlayer*currScore>=100000){
                    board[i][j]=0;
                    return currScore;
                }
                updateBounds(i, j);
                int nextStepValue = calculateHelper(-currPlayer, curr+1);
                upperBound = upper;
                lowerBound = lower;
                leftBound = left;
                rightBound = right;
                if((currPlayer*currScore>=10000&&-currPlayer*nextStepValue<100000)||
                    (currPlayer*currScore>=4000&&currPlayer*currScore<10000
                        &&-currPlayer*nextStepValue<10000)){
                    board[i][j]=0;
                    return currScore;
                }
                
                int currWinValue = currPlayer*(currScore+nextStepValue);
                if(currWinValue>best){
                    best = currWinValue;
                    //bestCurrScore = currScore;
                    // row = i;
                    // col = j;
                }
                board[i][j]=0;
            }
        }
    }
    if(!existPossibleStep){
        return 0;
    }
    if(currPlayer == 1){
        return best;
    }
    else{
        return (-1)*best;
    }
}
pair<int, int> gobang::AICalculate(int currPlayer){
    int best=-2147483648;
    int row, col;
    int upper = upperBound;
    int lower = lowerBound;
    int left = leftBound;
    int right = rightBound;
    for(int i=upper; i<=lower; i++){
        for(int j=left; j<=right; j++){
            if(isAIPossibleStep(i, j)){
                board[i][j]=currPlayer;
                int currScore = stepScore(i, j);
                if(currPlayer*currScore>=100000){
                    board[i][j]=0;
                    return std::make_pair(i, j);
                }
                updateBounds(i, j);
                int nextStepValue = calculateHelper(-currPlayer, 2);
                upperBound = upper;
                lowerBound = lower;
                leftBound = left;
                rightBound = right;
                if((currPlayer*currScore>=10000&&-currPlayer*nextStepValue<100000)||
                    (currPlayer*currScore>=4000&&currPlayer*currScore<10000
                        &&-currPlayer*nextStepValue<10000)){
                    board[i][j]=0;
                    return std::make_pair(i, j);
                }
                int currWinValue = currPlayer*(currScore+nextStepValue);
                if(currWinValue>best){
                    best = currWinValue;
                    row = i;
                    col = j;
                }
                cout<<i<<" "<<j<<" "<<currScore<<" "<<currWinValue<<endl;
                board[i][j]=0;
            }
        }
    }
    return std::make_pair(row, col);
}
bool gobang::AIMove(int currPlayer, int currStep){
    if(currStep==1){
        board[7][7]=currPlayer;
        //updateBounds(7, 7);
        return false;
    }
    pair<int, int> temp = AICalculate(currPlayer);
    board[temp.first][temp.second]=currPlayer;
    cout<<"AI chose: "<<temp.first<<" "<<temp.second<<endl;
    updateBounds(temp.first, temp.second);
    int n = stepScore(temp.first, temp.second);
    cout<<"AI step score: "<<n<<endl;
    if(n*currPlayer>=100000){
        return true;
    }
    else{
        return false;
    }

}

void gobang::printBoard(){
    cout<<"  ";
    for(int i=0; i<15; i++){
        if(i<10){
            cout<<" "<<i;
        }
        else{
            cout<<i;
        }
    }
    cout<<endl;
    for(int i=0; i<15; i++){
        if(i<10){
            cout<<" "<<i;
        }
        else{
            cout<<i;
        }
        for(int j=0; j<15; j++){
            if(board[i][j]==0){
                cout<<" "<<".";
            }
            else if(board[i][j]==1){
                cout<<" "<<"X";
            }
            else if(board[i][j]==-1){
                cout<<" "<<"O";
            }
        }
        cout<<endl;
    }
}

void gobang::clearBoard(){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            board[i][j]=0;
        }
    }
}

void gobang::startGame(){
    int curr;
    char start = 'y';
    while(start == 'y'){
        curr=0;
        cout<<"Do you wanna be the first(1) or the second(0)? ";
        cin>>seq;
        bool anybodyWin = false;
        while(curr<225){
            curr++;
            if(curr%2==seq){
                printBoard();
                if(playerMove(rep[seq])){
                    cout<<"You win. Cong!"<<endl;
                    anybodyWin = true;
                    break;
                }
            }
            else{
                printBoard();
                if(AIMove(rep[1-seq], curr)){
                    cout<<"AI wins."<<endl;
                    anybodyWin = true;
                    break;
                }
            }
        }
        cout<<endl;
        if(!anybodyWin){
            cout<<"Tie"<<endl;
        }
        
        printBoard();
        cout<<"Another game(y/n)? ";
        cin>>start;
        clearBoard();
    }

}