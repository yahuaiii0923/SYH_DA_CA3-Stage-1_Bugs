//
// Created by plo on 25/04/2025.
//

#ifndef BUG_H
#define BUG_H

#include <list>


struct Position {
    int x;
    int y;
};

enum class Direction {
    North = 1,
    East = 2,
    South = 3,
    West = 4
};

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;
    int killedBy = -1;

public:
    Bug(int id, int x, int y, int dir, int size);
    virtual ~Bug() = default;

    // getters
    int getId() const;
    int getPositionX() const;
    int getPositionY() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    std::list<Position> getPath() const;
    int getKilledBy() const;

    // setters
    void setDirection(Direction dir);
    void setAlive(bool status);
    void increaseSize(int amount);
    void setKilledBy(int killerId);

    virtual void move() = 0; // make bug an abstract class


    bool isWayBlocked() const;
};

#endif // BUG_H