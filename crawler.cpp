//
// Created by Siew Yahuai on 31/03/2025.
//

#include "crawler.h"

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

