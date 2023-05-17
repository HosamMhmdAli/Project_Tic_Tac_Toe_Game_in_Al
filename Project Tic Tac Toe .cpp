#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

class Move {
public:
    int row;
    int column;
};

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
const char HUMAN = 'X';
const char AI = 'O';
const int WIN_STATE = 2, LOSE_STATE = -2, DRAW_STATE = 1, NOT_FINISHED_STATE = 0;

bool equals3(char a, char b, char c) {
    return a == b && b == c && a != ' ';
}

int checkGameState() {
    int gameState = NOT_FINISHED_STATE;

    /* winning from first diagonal */
    if (equals3(board[0][0], board[1][1], board[2][2])) {
        gameState = board[0][0] == AI ? WIN_STATE : LOSE_STATE;
    }
    /* winning from second diagonal */
    if (equals3(board[0][2], board[1][1], board[2][0])) {
        gameState = board[0][2] == AI ? WIN_STATE : LOSE_STATE;
    }
    /* wining from rows */
    for (int i = 0; i < 3; i++) {
        if (equals3(board[i][0], board[i][1], board[i][2])) {
            gameState = board[i][0] == AI ? WIN_STATE : LOSE_STATE;
        }
    }
    /* wining from columns */
    for (int i = 0; i < 3; i++) {
        if (equals3(board[0][i], board[1][i], board[2][i])) {
            gameState = board[0][i] == AI ? WIN_STATE : LOSE_STATE;
        }
    }
    int emptyCells = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                emptyCells++;
            }
        }
    }
    /* check if it is drawing */
    if (gameState == NOT_FINISHED_STATE && emptyCells == 0) {
        gameState = DRAW_STATE;
    }
    return gameState;
}

int minimax(int depth, bool isMaximizing) {
    int gameState = checkGameState();
    if (gameState != NOT_FINISHED_STATE || depth == 0) {
        return gameState;
    }

    if (isMaximizing) {
        int bestScore = INT32_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Is the cell available?
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    int score = minimax(depth - 1, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }

        return bestScore;
    }
    else {
        int bestScore = INT32_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Is the cell available?
                if (board[i][j] == ' ') {
                    board[i][j] = HUMAN;
                    int score = minimax(depth - 1, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

Move findBestMove() {
    int bestVal = INT32_MIN;
    Move bestMove = Move();
    bestMove.row = -1;
    bestMove.column = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == ' ') {
                // Make the move
                board[i][j] = AI;
                // compute evaluation function for this move
                int moveVal = minimax(100, false);

                // Undo after modifying the original board
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.column = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void displayBoard() {
    cout<<nl;
    cout<<"-------\n|";
    string printedSymbols;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
                case ' ' :
                    printedSymbols = " |";
                    break;
                case HUMAN :
                    printedSymbols = "X|";
                    break;
                case AI :
                    printedSymbols = "O|";
                    break;
            }
            cout<<printedSymbols;
        }
        cout<<"\n-------\n|";
    }
}


int main() {
    int x, y;
    while (checkGameState() == NOT_FINISHED_STATE) {
        cin>>x>>y;
        if (board[x][y] == ' ') {
            board[x][y] = HUMAN;
            displayBoard();    //will be modified
            if (checkGameState() != NOT_FINISHED_STATE) {
                break;
            }
            Move best = findBestMove();
            cout<<"bestMove: " << best.row << " row, " << best.column << " col"<<nl;
            board[best.row][best.column] = AI;   //will be modified
            displayBoard();
        }
        else {
            cout<<"you can't write on this cell, it is already filled"<<nl;
        }

    }
    int gameFinalState = checkGameState();
    if (gameFinalState == DRAW_STATE) {
        cout<<"It is Draw !"<<nl;   //will be modified with Toast
    }
    else if (gameFinalState == LOSE_STATE) {
        cout<<"The Winner is X !"<<nl;  //will be modified with Toast
    }
    else {
        cout<<"The winner is O !"<<nl;//will be modified with Toast
    }
    return 0;
}