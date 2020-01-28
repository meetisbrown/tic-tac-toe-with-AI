/***************************************************************************
    Compiling the program
****************************************************************************
The program should be compiled using the following flags:
-std=c99
-Wall
compiling: gcc assn1.c -stc99 -Wall -o assn1
****************************************************************************
    Running the program
****************************************************************************
Running: ./assn1
****************************************************************************

Course name: CIS 1500
Student Name: Nareshri Babu
Username: nbabu
File name: babuNareshriA3.c
Last modified date: November 28, 2018

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic integrity;
2) I have completed the Computing with Integrity Tutorial on Moddle;
3) I have achieved at least 80% in the Computing with Integrity Self Test.

I assert that this work is my own. I have appropriately acknowledged any
and all material (data, images, ideas or words) that I have used, whether
directly quoted or paraphrased. Furthermore, I certify that this assignment
was prepared by me specifically for this course.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid (int, int, int);
int isBoardFull (char [N][N]);
void createInitialBoard (char [N][N]);
void readUserMove (int *, int *);
void printCurrentBoard (char [N][N]);
int getComputerMove (char [N][N], int *, int *, int, int);
int gameWon (char [N][N], char);
int computerPlaysToWin (char [N][N], int *, int *);
void computerPlaysRandom (int *, int *, int, int);
void sumAllDimensions (char [N][N], int [N], int [N], int *, int *);
int memberOf (int, int [N]);
int computerPlaysToBlock (char [N][N], int *, int *);


int main() {

    int userRow, userCol, computerRow, computerCol;
    int taken;
    char board[N][N];
    char winner = 'N';

    srand(time(NULL));

    printf("This tic-tac-toe board is of size %d by %d\n", N, N);

    printf("Player symbol: X \nComputer symbol: O\n\n");

    printf("Here is the board - spaces are indicated by a ?\n");

    createInitialBoard(board);          //create a 3 X 3 board with '?' in each cell

    while ((winner != 'Y') && !(isBoardFull(board))) {   //while there is no winner and the board is not full
        taken = 0;

        while (!(taken)) {              //loop used to accept valid row and col values from the user
            readUserMove(&userRow, &userCol);    //get user's move
            printf("You chose row %d and column %d \n", userRow, userCol);

            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N)) {    //validate user's move
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }

            if (board[userRow - 1][userCol - 1] == '?') {        //if cell is unoccupied
                board[userRow - 1][userCol - 1] = 'X';           //store an X there
                taken = 1;
            }
            else {
                taken = 0;         //otherwise inform the user to enter values again
                printf("That spot is taken = please try another one\n");
            }
        } //end of while (!taken)

        if (gameWon(board, 'X')) {   //check if the user wins - game will end if the user does win
            printf("Congrats - you won against the computer :)\n");
            winner = 'Y';
        }
        else if (!(isBoardFull(board))) {     //check if the board is already full
            taken = 0;

            while (!(taken)) {
                getComputerMove(board, &computerRow, &computerCol, userRow - 1, userCol - 1);   //get computer's row and col

                if (board[computerRow][computerCol] == '?') {      //check if the cell is unoccupied
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
                }
                else {
                    taken = 0;       //That spot is taken - computer - try another one
                }
            }

            printf("Computer chose row %d and column %d \n", computerRow + 1, computerCol + 1);

            if (gameWon(board, 'O')) {      //check if the computer wins - game must end if it does
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }

        printCurrentBoard(board);

        printf("\nPress enter to continue \n");
        getchar();

    }    //end of while

    if (winner != 'Y') {
        printf("Game was a tie - no winner!\n\n");
    }

    return 0;

}

void createInitialBoard(char board [N][N]) {

    //declare variables
    int i;
    int j;

    printf("\n\n");

    //create and print board
    for(i = 0; i < N; i++) {

        for(j = 0; j < N; j++) {

            board[i][j] = '?';
            printf(" %c ", board[i][j]);

            if (j != 2) {
                printf("|");
            }
        }

        if (i != 2) {
            printf("\n------------\n");
        }
    }

    printf("\n\n\n");

    return;

}

void printCurrentBoard(char board[N][N]) {

    //declare variables
    int i;
    int j;

    //print board using a loop
    for(i = 0; i < N; i++) {

        for(j = 0; j < N; j++) {

            printf(" %c ", board[i][j]);

            if (j != 2) {
                printf("|");
            }
        }

        if (i != 2) {
            printf("\n------------\n");
        }
    }

    printf("\n\n");

    return;
}

int isInputValid(int entered, int minimum, int maximum) {

    int result;

    //if entered number is between 1 to 3 we return 1 or else we return 0
    if ((entered >=  minimum) && (entered <= maximum)) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
}

int isBoardFull(char board[N][N]) {

    //declare variables
    int returnNum;
    int storeVariable = 1;
    int i;
    int j;

    //check all spaces on board
    for (i = 0; i < N; i++) {

        for (j = 0; j < N; j++) {

            if (board[i][j] == '?') {
                storeVariable = 0;
            }
        }
    }

    if (storeVariable == 0) {
        returnNum = 0;
    }
    else {
        returnNum = 1;
    }

    return returnNum;
}

void readUserMove(int * userRow, int * userCol) {

    //Ask and store user row and column
    printf("Your move - enter numbers between 1 and 3\n");

    printf("Enter row number: ");
    scanf("%d", userRow);

    printf("Enter column number: ");
    scanf("%d", userCol);
    printf("\n");

    return;
}


int getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol) {

/*
    This function determines computer's move in terms of row (computerRow) and column (computerCol)
    and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
    find one, then it calls function computerPlaysRandom in its attempt to place its symbol in the same
    row or column as the user (userRow, userCol)
*/

    int winningSpot = 0;
    int blocked = 1;               // this declaration is required if you attempt the bonus part

    winningSpot = computerPlaysToWin(board, computerRow, computerCol);

    if (!winningSpot) {                //if computer does find a winning spot, then it plays to block the user
       // computerPlaysRandom(computerRow, computerCol, userRow, userCol);


       // If you attempt the bonus part, then uncomment the code below and use it to first try and block user move
       // If unsuccessful, then it picks row and col (pseudo) randomly


        blocked = computerPlaysToBlock(board, computerRow, computerCol);
        if (blocked == 0) {
            computerPlaysRandom(computerRow, computerCol, userRow, userCol);
        }
    }

    return winningSpot;
}

int gameWon (char board[N][N], char symbol) {

    //declare variables
    int i;
    int j;
    int score[N][N];
    int sumRow[N];
    int sumCol[N];
    int sumDiag1 = 0;
    int sumDiag2 = 0;
    int win = 0;

    //Loop for row
    for(i = 0; ((i < N) && (win == 0)); i++) {

        sumRow[i] = 0;

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }

            sumRow[i] = sumRow[i] + score[i][j];

            if ((symbol == 'O') && (sumRow[i] == 12)) {
                win = 1;
            }
            else if ((symbol == 'X') && (sumRow[i] == 3)) {
                win = 1;
            }
        }
    }

    //Loop for Column
    for(j = 0; ((j < N) && (win == 0)); j++) {

        sumCol[j] = 0;

        for(i = 0; i < N; i++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }

            sumCol[j] = sumCol[j] + score[i][j];

            if ((symbol == 'O') && (sumCol[j] == 12)) {
                win = 1;
            }
            else if ((symbol == 'X') && (sumCol[j] == 3)) {
                win = 1;
            }
        }
    }

    //Loop for diagonal one (Left Diagonal)
    for (i = 0; ((i < N) && (win == 0)); i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }
        }
    }

    sumDiag1 = score[0][0] + score[1][1] + score[2][2];

    if ((symbol == 'O') && (sumDiag1 == 12)) {
        win = 1;
    }
    else if ((symbol == 'X') && (sumDiag1 == 3)) {
        win = 1;
    }

    //Loop for diagonal two (Right Diagonal)

    for(i = 0; ((i < N) && (win == 0)); i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }
        }
    }

    sumDiag2 = score[0][2] + score[1][1] + score[2][0];

    if ((symbol == 'O') && (sumDiag2 == 12)) {
        win = 1;
    }
    else if ((symbol == 'X') && (sumDiag2 == 3)) {
        win = 1;
    }

    return win;
}


int computerPlaysToWin (char board [N][N], int * cRow, int * cCol) {

    //declare variables
    int i;
    int j;
    int score[N][N];
    int sumRow[N];
    int sumCol[N];
    int sumDiag1 = 0;
    int sumDiag2 = 0;
    int computerWin = 0;
    int storeI = 0;
    int storeJ = 0;

    //Loop for Row
    for( i = 0; ((i < N) && (computerWin == 0)); i++) {

        sumRow[i] = 0;
        storeI = 5;
        storeJ = 5;

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
                storeI = i;
                storeJ = j;
            }

            sumRow[i] = sumRow[i] + score[i][j];

            if (sumRow[i] == 8) {
                if (board[storeI][storeJ] == '?') {
                    *cRow = i;
                    *cCol = j;
                    computerWin = 1;
                }
            }
        }
    }

    //Loop for column
    for(j = 0; ((j < N) && (computerWin == 0)); j++) {

        sumCol[j] = 0;
        storeI = 5;
        storeJ = 5;

        for(i = 0; i < N; i++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
                storeI = i;
                storeJ = j;
            }

            sumCol[j] = sumCol[j] + score[i][j];

            if (sumCol[j] == 8) {

                if (board[storeI][storeJ] == '?') {
                    *cRow = i;
                    *cCol = j;
                    computerWin = 1;
                }
            }
        }
    }

    //Loop for diagonal one
    for(i = 0; ((i < N) && (computerWin == 0)); i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;

                if (((i == 0) && (j == 0)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 2))) {
                    storeI = i;
                    storeJ = j;
                }
            }
        }
    }

    sumDiag1 = score[0][0] + score[1][1] + score[2][2];

    if (sumDiag1 == 8) {
        if (board[storeI][storeJ] == '?') {
            *cRow = storeI;
            *cCol = storeJ;
            computerWin = 1;
        }
    }

    //Loop for diagonal two
    for(i = 0; ((i < N) && (computerWin == 0)); i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;

                if(((i == 0) && (j == 2)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 0))) {
                    storeI = i;
                    storeJ = j;
                }
            }
        }
    }

    sumDiag2 = score[0][2] + score[1][1] + score[2][0];

    if (sumDiag2 == 8) {

        if (board[storeI][storeJ] == '?') {
            *cRow = storeI;
            *cCol = storeJ;
            computerWin = 1;
        }
    }

    return computerWin;
}

void computerPlaysRandom (int * cRow, int * cCol, int uRow, int uCol) {

    //declare variables
    int num;
    int chosen = 0;
    int i;
    int j;

    //seed using time
    srand((int)time(0));

    while(chosen != 1) {

        //rand function
        num = rand() % 3;
        i = rand() % 3;
        j = rand() % 3;

        //randomize based on the random number between 0 and 2

        //same row
        if (num == 0) {
            *cRow = uRow;
            *cCol = j;
            chosen = 1;
        }

        //same column
        if (num == 1) {
            *cRow = i;
            *cCol = uCol;
            chosen = 1;
        }

        //same diagonal
        if (num == 2) {

            //diagonal 1
            if (uCol == uRow) {
                if (((i == 0) && (j == 0)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 2))) {
                    *cRow = i;
                    *cCol = j;
                    chosen = 1;
                }
            }

            //diagonal 2
            if (uRow == 2 - uCol) {
                if (((i == 0) && (j == 2)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 0))) {
                    *cRow = i;
                    *cCol = j;
                    chosen = 1;
                }
            }
        }
    }

    return;
}

void sumAllDimensions (char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD) {

    //declare variables
    int i;
    int j;
    int score[N][N];

    //Loop for Row
    for(i = 0; i < N; i++) {

        sumR[i] = 0;

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }

            sumR[i] = sumR[i] + score[i][j];
        }
    }

    //Loop for column
    for(j = 0; j < N; j++) {

        sumC[j] = 0;

        for(i = 0; i < N; i++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }

            sumC[j] = sumC[j] + score[i][j];

        }
    }

    //Loop for diagonal one
    for(i = 0; i < N; i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }
        }
    }

    *sumLD = score[0][0] + score[1][1] + score[2][2];

    //Loop for diagonal two
    for(i = 0; i < N; i++) {

        for(j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
            }
        }
    }

    *sumRD = score[0][2] + score[1][1] + score[2][0];

    return;
}


int computerPlaysToBlock (char board[N][N], int * cRow, int * cCol) {

    //declare variables
    int i;
    int j;
    int score[N][N];
    int sumCol[N];
    int sumRow[N];
    int storeI = 0;
    int storeJ = 0;
    int returnResult = 0;
    int sumDiag1 = 0;
    int sumDiag2 = 0;

    //Loop for Row
    for (i = 0; ((i < N) && (returnResult == 0)); i++) {

        sumRow[i] = 0;
        storeI = 5;
        storeJ = 5;

        for (j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
                storeI = i;
                storeJ = j;
            }
            sumRow[i] = sumRow[i] + score[i][j];

            if (sumRow[i] == 2) {
                if (board[storeI][storeJ] == '?') {
                    *cRow = storeI;
                    *cCol = storeJ;
                    returnResult = 1;
                }
            }
        }
    }

    //Loop for Column
    for (j = 0; ((j < N) && (returnResult == 0)); j++) {

        sumCol[j] = 0;
        storeI = 5;
        storeJ = 5;

        for (i = 0; i < N; i++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;
                storeI = i;
                storeJ = j;
            }

            sumCol[j] = sumCol[j] + score[i][j];

            if (sumCol[j] == 2) {
                if (board[storeI][storeJ] == '?') {
                    *cRow = storeI;
                    *cCol = storeJ;
                    returnResult = 1;
                }
            }
        }
    }

    //Loop for Diagonal one
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;

                if (((i == 0) && (j == 0)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 2))) {
                    storeI = i;
                    storeJ = j;
                }
            }
        }
    }

    sumDiag1 = score[0][0] + score[1][1] + score[2][2];

    if (sumDiag1 == 2) {
        if (board[storeI][storeJ] == '?') {
            *cRow = storeI;
            *cCol = storeJ;
            returnResult = 1;
        }
    }

    //Loop for Diagonal 2
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {

            if (board[i][j] == 'X') {
                score[i][j] = 1;
            }
            if (board[i][j] == 'O') {
                score[i][j] = 4;
            }
            if (board[i][j] == '?') {
                score[i][j] = 0;

                if (((i == 0) && (j == 2)) || ((i == 1) && (j == 1)) || ((i == 2) && (j == 0))) {
                    storeI = i;
                    storeJ = j;
                }
            }
        }
    }

    sumDiag2 = score[0][2] + score[1][1] + score[2][0];

    if (sumDiag2 == 2) {
        if (board[storeI][storeJ] == '?') {
            *cRow = storeI;
            *cCol = storeJ;
            returnResult = 1;
         }
    }

    return returnResult;
}
