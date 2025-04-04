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
#include <cstdlib>


Board::Board() : gameOver(false) {
    // Initialize cells map
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

// Board.cpp
void Board::updateCells() {
    // Clear existing cells
    for (auto& cell : cells) {
        cell.second.clear();
    }

    // Update cells with alive crawlers
    for (Crawler* crawler : crawlers) {
        if (crawler->isAlive()) {
            int x = crawler->getPositionX();
            int y = crawler->getPositionY();
            cells[{x, y}].push_back(crawler);
        }
    }
}

void Board::handleFights() {
    for (auto& cellEntry : cells) {
        auto& bugsInCell = cellEntry.second;
        if (bugsInCell.size() <= 1) continue;

        // Find the largest bug(s)
        int maxSize = 0;
        for (Crawler* bug : bugsInCell) {
            if (bug->getSize() > maxSize) {
                maxSize = bug->getSize();
            }
        }

        // Collect contenders of max size
        std::vector<Crawler*> contenders;
        for (Crawler* bug : bugsInCell) {
            if (bug->getSize() == maxSize) {
                contenders.push_back(bug);
            }
        }

        // Randomly select a winner if multiple contenders
        Crawler* winner = contenders[rand() % contenders.size()];
        int totalSizeEaten = 0;

        // Kill other bugs and update winner's size
        for (Crawler* bug : bugsInCell) {
            if (bug != winner) {
                totalSizeEaten += bug->getSize();
                bug->setAlive(false);
            }
        }

        winner->increaseSize(totalSizeEaten);
        bugsInCell.clear();
        bugsInCell.push_back(winner);
    }
    updateCells(); // Refresh cell data after fights
}

//(1)Initialize Board
void Board::initializeBoard(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        char type, comma;
        int id, x, y, dir, size;

        // Parse line format: C,101,0,0,4,2
        ss >> type >> comma >> id >> comma >> x >> comma >> y >> comma >> dir >> comma >> size;

        if (type == 'C') {
            crawlers.push_back(new Crawler(id, x, y, dir, size));
        }
    }
    updateCells(); // Update cell positions
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

Crawler* Board::findBug(int id) const {
    for (Crawler* crawler : crawlers) {
        if (crawler->getId() == id) {
            return crawler;
        }
    }
    return nullptr; // Return nullptr if not found
}


