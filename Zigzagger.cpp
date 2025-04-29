//
// Created by plo on 27/04/2025.
//

#include "Zigzagger.h"
#include <cstdlib>

Zigzagger::Zigzagger(int id, int x, int y, int dir, int size)
    : Bug(id, x, y, dir, size), zigPhase(true) {
    //starts with forward movement
}

void Zigzagger::move() {
    // Don't move if bug is dead
    if (!this->isAlive()) {
        return;
    }


    while (this->isWayBlocked()) {
        int randInt = std::rand() % 4 + 1;
        Direction dir;
        switch (randInt) {
            case 1:
                dir = Direction::North;
                break;
            case 2:
                dir = Direction::East;
                break;
            case 3:
                dir = Direction::South;
                break;
            case 4:
                dir = Direction::West;
                break;
        }
        this->setDirection(dir);
    }


    Position newPos;
    newPos.x = this->getPositionX();
    newPos.y = this->getPositionY();
    Direction currentDir = this->getDirection();

    if (zigPhase) {

        switch (currentDir) {
            case Direction::North:
                newPos.y--;
                break;
            case Direction::East:
                newPos.x++;
                break;
            case Direction::South:
                newPos.y++;
                break;
            case Direction::West:
                newPos.x--;
                break;
        }
    } else {

        switch (currentDir) {
            case Direction::North:
                newPos.y--;
                newPos.x++;
                break;
            case Direction::East:
                newPos.x++;
                newPos.y++;
                break;
            case Direction::South:
                newPos.y++;
                newPos.x--;
                break;
            case Direction::West:
                newPos.x--;
                newPos.y--;
                break;
        }
    }


    if (newPos.x < 0 || newPos.x > 9 || newPos.y < 0 || newPos.y > 9) {

        newPos.x = this->getPositionX();
        newPos.y = this->getPositionY();
        switch (currentDir) {
            case Direction::North:
                newPos.y--;
                break;
            case Direction::East:
                newPos.x++;
                break;
            case Direction::South:
                newPos.y++;
                break;
            case Direction::West:
                newPos.x--;
                break;
        }
    }


    this->path.push_back(newPos);


    zigPhase = !zigPhase;
}