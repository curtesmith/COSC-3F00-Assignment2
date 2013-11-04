/*
 * File: main.cpp
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "main.h"
#include "Game.h"
#include <list>
#include <thread>

using namespace std;

bool isValidMove(int move) {
    if (move < 0) {
        return false;
    } else {
        return gameBoard[move] != "X" && gameBoard[move] != "O";
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
    } else if (move + 8 < NUMBER_OF_POSITIONS) {
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

    cout << "|" << gameBoard[0] << "|" << gameBoard[1] << "|" << gameBoard[2] << "|\t"
            << "|" << gameBoard[8] << "|" << gameBoard[9] << "|" << gameBoard[10] << "|\t"
            << "|" << gameBoard[16] << "|" << gameBoard[17] << "|" << gameBoard[18] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl;

    cout << " |" << gameBoard[3] << "|" << gameBoard[4] << "|\t"
            << " |" << gameBoard[11] << "|" << gameBoard[12] << "|\t"
            << " |" << gameBoard[19] << "|" << gameBoard[20] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl;

    cout << "|" << gameBoard[5] << "|" << gameBoard[6] << "|" << gameBoard[7] << "|\t"
            << "|" << gameBoard[13] << "|" << gameBoard[14] << "|" << gameBoard[15] << "|\t"
            << "|" << gameBoard[21] << "|" << gameBoard[22] << "|" << gameBoard[23] << "|" << endl;

    for (int i = 1; i < 4; i++) {
        cout << " - - - \t";
    }
    cout << endl << endl;

    cout << "You have " << playersScore << " winning alignments" << endl;
    cout << "Your opponent has " << opponentsScore << " winning alignments" << endl;
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
        gameBoard[move] = "X";
        playersMoves[playerCurrentMove] = move;
        playersScore = countWinningAlignments(playersMoves);
        playerCurrentMove++;
    } else {
        gameBoard[move] = "O";
        opponentsMoves[opponentCurrentMove] = move;
        opponentsScore = countWinningAlignments(opponentsMoves);
        opponentCurrentMove++;
    }
}

void announceWinner() {
    if (playersScore > opponentsScore) {
        cout << "CONGRATULATIONS, YOU WIN!!!" << endl;
    } else if (playersScore == opponentsScore) {
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