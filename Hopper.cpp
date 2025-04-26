//
// Created by plo on 25/04/2025.
//
#include "Hopper.h"
#include <iostream>

Hopper::Hopper(int id, int x, int y, int dir, int size)
    : Bug(id, x, y, dir, size) {
    // Initialize hopLength to random value between 2-4
    hopLength = (rand() % 3) + 2; // 2, 3, or 4
}

void Hopper::move() {
    if (!alive) return;

    Position newPos = position;
    bool moved = false;
    int attempts = 0;
    const int maxAttempts = 10; // Prevent infinite loops

    while (!moved && attempts < maxAttempts) {
        attempts++;

        if (isWayBlocked()) {
            // Change direction randomly if blocked
            direction = static_cast<Direction>((rand() % 4) + 1);
            continue;
        }

        // Calculate new position based on direction
        switch (direction) {
            case Direction::North:
                newPos.y = (position.y - hopLength >= 0) ?
                          position.y - hopLength : 0;
            break;
            case Direction::East:
                newPos.x = (position.x + hopLength <= 9) ?
                          position.x + hopLength : 9;
            break;
            case Direction::South:
                newPos.y = (position.y + hopLength <= 9) ?
                          position.y + hopLength : 9;
            break;
            case Direction::West:
                newPos.x = (position.x - hopLength >= 0) ?
                          position.x - hopLength : 0;
            break;
        }

        moved = true;
    }

    if (moved) {
        position = newPos;
        path.push_back(position); // Record new position

        // Debug output (optional)
        std::cout << "Hopper " << id << " hopped to ("
                  << position.x << "," << position.y << ")\n";
    } else {
        std::cerr << "Hopper " << id << " couldn't find valid move!\n";
    }
}