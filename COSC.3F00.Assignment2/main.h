/*
 * File: main.h
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */
#ifndef MAIN_H
#define	MAIN_H

#define MAX_MOVES 24
#define NUMBER_OF_WINNING_ALIGNMENTS 38
#define NUMBER_OF_POSITIONS 24

#include "Game.h"

std::string gameBoard[NUMBER_OF_POSITIONS] = {"F", "G", "H", "D", "E", "A", "B", "C", "F", 
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
int playersScore, opponentsScore = 0;
std::list<int> board;
Game game;

#endif	/* MAIN_H */

