/*
 * File: Player.cpp
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */
#include "Player.h"

Player::Player() {
    initializeMoves();
    score = 0;
    currentMove = -1;
}

Player::~Player() {
}

void Player::initializeMoves() {
    for(int i=0; i<MAX_MOVES/2; i++) {
        moves[i] = -1;
    }
}

void Player::setNextMove(int move) {
    currentMove++;
    moves[currentMove] = move;
}

int* Player::getMoves() {
    return moves;
}

void Player::setScore(int value) {
    score = value;
}

int Player::getScore() {
    return score;
}