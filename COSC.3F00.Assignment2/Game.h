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
    void calculateNextMove(std::list<int> board);
    void setBoard(std::list<int> board);
    void notify();
private:
    int nextMove;
    bool running;
    std::mutex mtx;
    std::condition_variable cv;
    std::list<int> board;
    int getNumberOfMovesRemaining(std::list<int> board);
};

#endif	/* GAME_H */

