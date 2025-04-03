//
// Created by plo on 02/04/2025.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>
#include <random>


Board::Board() : gameOver(false) {

  //initialise cell map to be empty

  for(int i = 0; i < 10; i++) {

    for(int j = 0; j < 10; j++) {
      cells[{i, j}] = std::vector<Crawler*>();
    }
    }
  }

Board::~Board() {
  for (auto crawler : crawlers) {
    delete crawler;
  }
  crawlers.clear();
  cells.clear();
}


//(2) DisplayAllBugs();
void Board::displayAllBugs() const {
    std::cout << "\n--- All Bugs ---\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(10) << "Type"
              << std::setw(10) << "Position"
              << std::setw(5) << "Size"
              << std::setw(10) << "Direction"
              << "Status\n";
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& bug : crawlers) {
        std::string directionStr;
        Direction dir = bug->getDirection();
        switch (dir) {
            case Direction::North: directionStr = "North"; break;
            case Direction::East: directionStr = "East"; break;
            case Direction::South: directionStr = "South"; break;
            case Direction::West: directionStr = "West"; break;
            default: directionStr = "Unknown";
        }

        std::cout << std::left << std::setw(5) << bug->getId()
                  << std::setw(10) << "Crawler"
                  << "(" << bug->getPositionX() << "," << bug->getPositionY() << ")" << std::setw(3) << " "
                  << std::setw(5) << bug->getSize()
                  << std::setw(10) << directionStr
                  << (bug->isAlive() ? "Alive" : "Dead")
                  << std::endl;
    }
}


void Board::tap() {

  for(Crawler* crawler : crawlers) {
    if(crawler->isAlive()) {
      crawler->move();
    }
    }

    updateCells();

    handleFights();

  std::cout << "Board tapped! All bugs moved and fights resolved." << std::endl;

  }


  void Board::displayAllCells() const {
    std::cout << "\n====== CELLS AND THEIR BUGS ======\n";

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            std::cout << "(" << x << "," << y << "): ";

            // find bugs at position
            auto it = cells.find({x, y});
            if (it != cells.end() && !it->second.empty()) {

                bool first = true;
                for (const Crawler* bug : it->second) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << "Crawler " << bug->getId();
                    first = false;
                }
            } else {
                // cell is empty
                std::cout << "empty";
            }
            std::cout << std::endl;
        }
    }
}


