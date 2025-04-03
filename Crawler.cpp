//
// Created by Siew Yahuai on 31/03/2025.
//

#include "crawler.h"
#include <cstdlib>
#include <ctime>

//constructor
Crawler::Crawler(int id, int x, int y, int dir, int size)
    :id(id), position{x,y}, direction(static_cast<Direction>(dir), size(size), alive(true){
  path.push_back(position);
}

//getter
cosnt int Crawler::getId(){
  return id;
}

const int Crawler::getPositionX(){
  return position.x;
}

const int Crawler::getPositionY(){
  return position.y;
}

const Direction Crawler::getDirection(){
  return Direction;
}

const int Crawler::getSize(){
  return size;
}

const bool Crawler::isAlive(){
  return alive;
}

const std::list<Position> Crawler::getPath(){
  return path;
}

//setter
void Crawler::setDirection(Direction dir){
  direction = dir;
}

void Crawler::setAlive(bool status){
  alive = status;
}

void Crawler::increaseSize(int amount) {
    size += amount;
}

void Crawler::move() {
    if (!alive) return;

    // Keep changing direction until movement is possible
    while (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1); // Random direction (1-4)
    }

    // Update position based on direction
    switch (direction) {
        case Direction::North: position.y--; break;
        case Direction::East:  position.x++; break;
        case Direction::South: position.y++; break;
        case Direction::West:  position.x--; break;
    }

    path.push_back(position); // Record new position
}

bool Crawler::isWayBlocked() const {
    switch (direction) {
        case Direction::North: return (position.y == 0);  // Top edge
        case Direction::East:  return (position.x == 9);  // Right edge
        case Direction::South: return (position.y == 9);  // Bottom edge
        case Direction::West:  return (position.x == 0); // Left edge
        default: return false;
    }
}