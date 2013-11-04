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
#include <list>
#include <thread>
#include "main.h"
#include "Game.h"
#include "Player.h"

std::string gameBoard[NUMBER_OF_POSITIONS] = {"F", "G", "H", "D", "E", "A", "B", "C", "F", 
        "G", "H", "D", "E", "A", "B", "C", "F", "G", "H", "D", "E", "A", "B", "C"};

int winningAlignments[NUMBER_OF_WINNING_ALIGNMENTS][3] = {{0, 1, 2}, {5, 6, 7},
    {8, 9, 10}, {13, 14, 15}, {16, 17, 18}, {21, 22, 23}, {0, 3, 6}, {1, 4, 7},
    {8, 11, 14}, {9, 12, 15}, {16, 19, 22}, {17, 22, 23}, {1, 3, 5}, {2, 4, 6},
    {9, 11, 13}, {10, 12, 14}, {17, 19, 21}, {18, 20, 22}, {0, 8, 16}, {1, 9, 17},
    {2, 10, 18}, {3, 11, 19}, {4, 12, 20}, {5, 13, 21}, {6, 14, 22}, {7, 15, 23},
    {0, 9, 18}, {5, 14, 23}, {2, 9, 16}, {7, 14, 21}, {0, 11, 22}, {1, 12, 23},
    {6, 11, 16}, {7, 12, 17}, {1, 11, 21}, {2, 12, 22}, {5, 11, 17}, {6, 12, 18}};

std::list<int> availablePegs;
Game game;
Player player;
Player opponent;

using namespace std;

bool isValidMove(int move) {
    if (move < 0) {
        return false;
    } else {
        return gameBoard[move] != "X" && gameBoard[move] != "O";
    }
}

void updateAvailablePegs(int move) {
    if (move >= 16) {
        availablePegs.remove(move - 16);
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
    if (alphaMove == "F" || alphaMove == "f") {
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

int askWhatIsNextMove(bool isPlayersTurn) {
    int move = 0;
    bool isDone = false;
    while (!isDone) {
        if (isPlayersTurn) {
            cout << endl << "Enter your move [pick any space by it's name from 'A' through 'H']: ";
            string alphaMove;
            cin >> alphaMove;
            move = convertAlphaMove(alphaMove);
        } else {
            move = resolveMove(game.getNextMove());
        }
        if (isValidMove(move))
            isDone = true;
    }
    updateAvailablePegs(move);
    if(isPlayersTurn) {
        game.setAvailablePegs(availablePegs);
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

    cout << "You have " << player.getScore() << " winning alignments" << endl;
    cout << "Your opponent has " << opponent.getScore() << " winning alignments" << endl;
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
        player.setNextMove(move);
        player.setScore(countWinningAlignments(player.getMoves()));
    } else {
        gameBoard[move] = "O";
        opponent.setNextMove(move);
        opponent.setScore(countWinningAlignments(opponent.getMoves()));
    }
}

void announceWinner() {
    if (player.getScore() > opponent.getScore()) {
        cout << "CONGRATULATIONS, YOU WIN!!!" << endl;
    } else if (player.getScore() == opponent.getScore()) {
        cout << "Tie game." << endl;
    } else {
        cout << "Sorry, you lose." << endl;
    }

}

bool endOfGame(int num) {
    return num == MAX_MOVES;
}

void initializeAvailablePegs() {
    for (int i = 0; i < 8; i++) {
        availablePegs.push_back(i);
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
    initializeAvailablePegs();
    bool isPlayersTurn = wouldYouLikeToGoFirst();
    thread gameThread(startGame);
    int i = 0;
    
    while (!endOfGame(i)) {
        displayGameInterface();
        int move = askWhatIsNextMove(isPlayersTurn);
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