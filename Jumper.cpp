//
// Created by plo on 25/04/2025.
//
#include "Jumper.h"
#include <cstdlib>

Jumper::Jumper(int id, int x, int y, int dir, int size)
    : Bug(id, x, y, dir, size), jumpCounter(0) {
}

void Jumper::move() {
    if (!alive) return;

    jumpCounter++;

    // every third jump reverse direction
    if (jumpCounter % 3 == 0) {
        // reverse direction
        switch (direction) {
            case Direction::North: direction = Direction::South; break;
            case Direction::East:  direction = Direction::West; break;
            case Direction::South: direction = Direction::North; break;
            case Direction::West:  direction = Direction::East; break;
        }
    }

    // keep changing direction until able to move
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }


    switch (direction) {
        case Direction::North:
            // check if we can jump 2 spaces
                if (position.y >= 2) {
                    position.y -= 2;
                } else {
                    // can only jump 1 space
                    position.y = 0;
                }
        break;
        case Direction::East:
            if (position.x <= 7) {
                position.x += 2;
            } else {
                position.x = 9;
            }
        break;
        case Direction::South:
            if (position.y <= 7) {
                position.y += 2;
            } else {
                position.y = 9;
            }
        break;
        case Direction::West:
            if (position.x >= 2) {
                position.x -= 2;
            } else {
                position.x = 0;
            }
        break;
    }

    path.push_back(position); // record new position
}