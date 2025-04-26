//
// Created by plo on 25/04/2025.
//
#include "Bug.h"
#include <cstdlib>

Bug::Bug(int id, int x, int y, int dir, int size)
    : id(id), position{x, y}, direction(static_cast<Direction>(dir)), size(size), alive(true) {
    path.push_back(position);
}

int Bug::getId() const {
    return id;
}

int Bug::getPositionX() const {
    return position.x;
}

int Bug::getPositionY() const {
    return position.y;
}

Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return size;
}

bool Bug::isAlive() const {
    return alive;
}

std::list<Position> Bug::getPath() const {
    return path;
}

int Bug::getKilledBy() const {
    return killedBy;
}

void Bug::setDirection(Direction dir) {
    direction = dir;
}

void Bug::setAlive(bool status) {
    alive = status;
}

void Bug::increaseSize(int amount) {
    size += amount;
}

void Bug::setKilledBy(int killerId) {
    killedBy = killerId;
}

bool Bug::isWayBlocked() const {
    switch (direction) {
        case Direction::North: return (position.y == 0);  // Top edge
        case Direction::East:  return (position.x == 9);  // Right edge
        case Direction::South: return (position.y == 9);  // Bottom edge
        case Direction::West:  return (position.x == 0);  // Left edge
        default: return false;
    }
}