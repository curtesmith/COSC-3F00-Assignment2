/*
 * File: Player.h
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "main.h"

class Player {
public:
    Player();
    virtual ~Player();
    void setNextMove(int move); 
    int* getMoves();
    void setScore(int value);
    int getScore();
private:
    int moves[MAX_MOVES/2];
    int score;
    int currentMove;
    void initializeMoves();
};

#endif	/* PLAYER_H */

