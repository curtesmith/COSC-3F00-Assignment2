/*
 * File: Game.cpp
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */

#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <list>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>

Game::Game() {
    nextMove = 0;
}

Game::~Game() {
}

void Game::start() {
    std::unique_lock<std::mutex> lck(mtx);
    running = true;
    while (running) {
        cv.wait(lck);
        if (running) {
            calculateNextMove(board);
        }
    }
}

void Game::setBoard(std::list<int> value) {
    board = value;
}

void Game::notify() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.notify_one();
}

void Game::stop() {
    running = false;
}

int Game::getNextMove() {
    return nextMove;
}

void Game::calculateNextMove(std::list<int> board) {
    int numberOfMovesRemaining = getNumberOfMovesRemaining(board);
    int move;

    if (numberOfMovesRemaining == 1) {
        move = 0;
    } else {
        srand(time(NULL));
        move = rand() % (numberOfMovesRemaining - 1);
    }

    std::list<int>::iterator pos = board.begin();
    std::advance(pos, move);
    nextMove = *pos;
}

int Game::getNumberOfMovesRemaining(std::list<int> board) {
    int result = 0;

    if (board.size() >= 8) {
        result = 8;
    } else if (board.size() < 8) {
        result = board.size();
    }

    return result;
}