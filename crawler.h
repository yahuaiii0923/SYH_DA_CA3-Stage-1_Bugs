//
// Created by Siew Yahuai on 31/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <list>

//coordinate on the 10x10 board
struct Position{
    int x;
    int y;
};

enum class Direction{
    North = 1,
    East = 2,
    South = 3,
    West = 4
  };

class Crawler{
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;


public:
    Crawler(int id, int x, int y, int dir, int size);

    void setDirection(Direction dir);
    void setAlive(bool status);
    void increaseSize(int amount);

    const int getId();
    const int getPositionX();
    const int getPositionY();
    const Direction getDirection();
    const int getSize();
    const bool isAlive();
    const std::list<Position> getPath();

    void move();
    bool isWayBlocked() const;
};

#endif //CRAWLER_H
