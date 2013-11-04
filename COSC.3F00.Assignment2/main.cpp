#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Game.h"
#include <list>
#include <thread>

#define MAX_MOVES 24
#define NUMBER_OF_WINNING_ALIGNMENTS 38
#define NUMBER_OF_SPACES 24

using namespace std;

string spaces[NUMBER_OF_SPACES] = {"F", "G", "H", "D", "E", "A", "B", "C", "F", 
        "G", "H", "D", "E", "A", "B", "C", "F", "G", "H", "D", "E", "A", "B", "C"};

int winningAlignments[NUMBER_OF_WINNING_ALIGNMENTS][3] = {{0, 1, 2}, {5, 6, 7},
    {8, 9, 10}, {13, 14, 15}, {16, 17, 18}, {21, 22, 23}, {0, 3, 6}, {1, 4, 7},
    {8, 11, 14}, {9, 12, 15}, {16, 19, 22}, {17, 22, 23}, {1, 3, 5}, {2, 4, 6},
    {9, 11, 13}, {10, 12, 14}, {17, 19, 21}, {18, 20, 22}, {0, 8, 16}, {1, 9, 17},
    {2, 10, 18}, {3, 11, 19}, {4, 12, 20}, {5, 13, 21}, {6, 14, 22}, {7, 15, 23},
    {0, 9, 18}, {5, 14, 23}, {2, 9, 16}, {7, 14, 21}, {0, 11, 22}, {1, 12, 23},
    {6, 11, 16}, {7, 12, 17}, {1, 11, 21}, {2, 12, 22}, {5, 11, 17}, {6, 12, 18}};

int playersMoves[MAX_MOVES / 2];
int opponentsMoves[MAX_MOVES / 2];
int playerCurrentMove, opponentCurrentMove = 0;
int playerWins, opponentWins = 0;
list<int> board;
Game game;

bool isValidMove(int move) {
    if (move < 0) {
        return false;
    } else {
        return spaces[move] != "X" && spaces[move] != "O";
    }
}

void updateBoard(int move) {
    if (move >= 16) {
        board.remove(move - 16);
    }
}

int resolveMove(int move) {
    int resolvedMove = -1;

    if (isValidMove(move)) {
        resolvedMove = move;
    } else if (move + 8 < NUMBER_OF_SPACES) {
        resolvedMove = resolveMove(move + 8);
    }

    return resolvedMove;
}

int convertAlphaMove(string alphaMove) {
    int result = -1;
    if (alphaMove == "F") {
        result = resolveMove(0);
    } else if (alphaMove == "G" || alphaMove == "g") {
        result = resolveMove(1);
    } else if (alphaMove == "H" || alphaMove == "h") {
        result = resolveMove(2);
    } else if (alphaMove == "D" || alphaMove == "d") {
        result = resolveMove(3);
    } else if (alphaMove == "E" || alphaMove == "e") {
        result = resolveMove(4);
    } else if (alphaMove == "A" || alphaMove == "a") {
        result = resolveMove(5);
    } else if (alphaMove == "B" || alphaMove == "b") {
        result = resolveMove(6);
    } else if (alphaMove == "C" || alphaMove == "c") {
        result = resolveMove(7);
    } else {
        result = -1;
    }

    return result;
}

int dialog(bool isPlayersTurn) {
    int move = 0;
    bool isDone = false;
    while (!isDone) {
        if (isPlayersTurn) {
            cout << endl << "Enter your move [pick any space by it's name from 'A' through 'H']: ";
            string alphaMove;
            cin >> alphaMove;
            move = convertAlphaMove(alphaMove);
        } else {
            //TODO: add a mutex and lock here
            move = resolveMove(game.getNextMove());
        }
        if (isValidMove(move))
            isDone = true;
    }
    updateBoard(move);
    if(isPlayersTurn) {
        game.setBoard(board);
        game.notify();
    }
    return move;
}


void displayGameInterface() {
    system("CLS");

    cout << "\t3D TIC-TAC-TOE" << endl;
    cout << "\t--------------" << endl;
    cout << "Spaces that you occupy on the board will hold a value of 'X'" << endl;
    cout << "and spaces your opponent holds will be 'O'" << endl << endl;
    
    for (int i = 1; i < 4; i++) {
        cout << " Tier " << i << "\t";
    }
    cout << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl;

    cout << "|" << spaces[0] << "|" << spaces[1] << "|" << spaces[2] << "|\t"
            << "|" << spaces[8] << "|" << spaces[9] << "|" << spaces[10] << "|\t"
            << "|" << spaces[16] << "|" << spaces[17] << "|" << spaces[18] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl;

    cout << " |" << spaces[3] << "|" << spaces[4] << "|\t"
            << " |" << spaces[11] << "|" << spaces[12] << "|\t"
            << " |" << spaces[19] << "|" << spaces[20] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl;

    cout << "|" << spaces[5] << "|" << spaces[6] << "|" << spaces[7] << "|\t"
            << "|" << spaces[13] << "|" << spaces[14] << "|" << spaces[15] << "|\t"
            << "|" << spaces[21] << "|" << spaces[22] << "|" << spaces[23] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl << endl;

    cout << "You have " << playerWins << " winning alignments" << endl;
    cout << "Your opponent has " << opponentWins << " winning alignments" << endl;
}

int countWinningAlignments(int moves[]) {
    int numberOfWins[NUMBER_OF_WINNING_ALIGNMENTS];
    for (int i = 0; i < NUMBER_OF_WINNING_ALIGNMENTS; i++) {
        numberOfWins[i] = 0;
    }

    int result = 0;

    for (int i = 0; i < MAX_MOVES / 2; i++) {
        for (int j = 0; j < NUMBER_OF_WINNING_ALIGNMENTS; j++) {
            for (int k = 0; k < 3; k++) {
                if (moves[i] == winningAlignments[j][k]) {
                    numberOfWins[j]++;
                    if (numberOfWins[j] == 3) {
                        result++;
                    }
                }
            }
        }
    }

    return result;
}

void tallyAlignments(bool isPlayer, int move) {
    if (isPlayer) {
        spaces[move] = "X";
        playersMoves[playerCurrentMove] = move;
        playerWins = countWinningAlignments(playersMoves);
        playerCurrentMove++;
    } else {
        spaces[move] = "O";
        opponentsMoves[opponentCurrentMove] = move;
        opponentWins = countWinningAlignments(opponentsMoves);
        opponentCurrentMove++;
    }
}

void announceWinner() {
    if (playerWins > opponentWins) {
        cout << "CONGRATULATIONS, YOU WIN!!!" << endl;
    } else if (playerWins == opponentWins) {
        cout << "Tie game." << endl;
    } else {
        cout << "Sorry, you lose." << endl;
    }

}

bool endGame(int num) {
    return num == MAX_MOVES;
}

void initializeBoard() {
    for (int i = 0; i < 8; i++) {
        board.push_back(i);
    }
}

void initialize() {
    initializeBoard();
    
    for(int i=0; i<MAX_MOVES/2; i++) {
        playersMoves[i] = -1;
        opponentsMoves[i] = -1;
    }
}

bool wouldYouLikeToGoFirst() {
    cout << "Welcome to 3D Tic-Tac-Toe" << endl;
    cout << "-------------------------" << endl;
    cout << "Would you like to go first (Y/N)? ";
    string response;
    cin >> response;
    return (response == "Y" || response == "y");
}

void startGame() {
    game.start();
}

int main(int argc, char** argv) {
    initialize();
    bool isPlayersTurn = wouldYouLikeToGoFirst();
    thread gameThread(startGame);
    int i = 0;
    
    while (!endGame(i)) {
        displayGameInterface();
        int move = dialog(isPlayersTurn);
        tallyAlignments(isPlayersTurn, move);
        isPlayersTurn = !isPlayersTurn;
        i++;
    }

    game.stop();
    game.notify();
    gameThread.join();

    displayGameInterface();
    announceWinner();
    return 0;
}