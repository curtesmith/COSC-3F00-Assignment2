/*
 * File: Game.h
 * Author: Curtis Smith 1851450
 * Course: COSC 3F00
 * Assignment: 2 
 * Due Date: Nov. 4th, 2013 4PM ET
 */

#ifndef GAME_H
#define	GAME_H

#include <string>
#include <list>
#include <mutex>
#include <condition_variable>

class Game {
public:
    Game();
    virtual ~Game();
    void start();
    void stop();
    int getNextMove();
    void calculateNextMove();
    void setAvailablePegs(std::list<int> availablePegs);
    void notify();
private:
    int nextMove;
    bool running;
    std::mutex mut;
    std::condition_variable conditionVar;
    std::list<int> availablePegs;
    int getNumberOfMovesRemaining();
};

#endif	/* GAME_H */

