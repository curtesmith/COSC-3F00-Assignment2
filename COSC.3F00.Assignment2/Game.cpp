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
    std::unique_lock<std::mutex> lck(mut);
    running = true;
    while (running) {
        conditionVar.wait(lck);
        if (running) {
            calculateNextMove();
        }
    }
}

void Game::setAvailablePegs(std::list<int> value) {
    availablePegs = value;
}

void Game::notify() {
    std::unique_lock<std::mutex> lck(mut);
    conditionVar.notify_one();
}

void Game::stop() {
    running = false;
}

int Game::getNextMove() {
    return nextMove;
}

void Game::calculateNextMove() {
    int numberOfMovesRemaining = getNumberOfMovesRemaining();
    int move;

    if (numberOfMovesRemaining == 1) {
        move = 0;
    } else {
        srand(time(NULL));
        move = rand() % (numberOfMovesRemaining - 1);
    }

    std::list<int>::iterator pos = availablePegs.begin();
    std::advance(pos, move);
    nextMove = *pos;
}

int Game::getNumberOfMovesRemaining() {
    int result = 0;

    if (availablePegs.size() >= 8) {
        result = 8;
    } else if (availablePegs.size() < 8) {
        result = availablePegs.size();
    }

    return result;
}