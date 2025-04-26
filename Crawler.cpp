//
// Created by Siew Yahuai on 31/03/2025.
//

#include "Crawler.h"
#include <cstdlib>

Crawler::Crawler(int id, int x, int y, int dir, int size)
    : Bug(id, x, y, dir, size) {
}

void Crawler::move() {
    if (!alive) return;

    // keep changing direction until able to move
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1); // Random direction (1-4)
    }

    // update position based on direction
    switch (direction) {
        case Direction::North: position.y--; break;
        case Direction::East:  position.x++; break;
        case Direction::South: position.y++; break;
        case Direction::West:  position.x--; break;
    }

    path.push_back(position); // record new position
}