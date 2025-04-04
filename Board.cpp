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
                bug->setKilledBy(winner->getId());
            }
        }

        winner->increaseSize(totalSizeEaten);
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

void Board::displayLifeHistory() const {
    for (const Crawler* crawler : crawlers) {
        std::cout << crawler->getId() << " Crawler Path: ";
        bool first = true;
        for (const Position& pos : crawler->getPath()) {
            if (!first) std::cout << ",";
            std::cout << "(" << pos.x << "," << pos.y << ")";
            first = false;
        }
        if (!crawler->isAlive()) {
            std::cout << " Eaten by " << crawler->getKilledBy();
        }
        std::cout << std::endl;
    }
}

void Board::writeHistoryToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error writing to file: " << filename << std::endl;
        return;
    }

    for (const Crawler* crawler : crawlers) {
        file << crawler->getId() << " Crawler Path: ";
        bool first = true;
        for (const Position& pos : crawler->getPath()) {
            if (!first) file << ",";
            file << "(" << pos.x << "," << pos.y << ")";
            first = false;
        }
        if (!crawler->isAlive()) {
            file << " Eaten by " << crawler->getKilledBy();
        }
        file << std::endl;
    }
}

bool Board::isGameOver() const {
    int aliveCount = 0;
    for (const Crawler* crawler : crawlers) {
        if (crawler->isAlive()) aliveCount++;
        if (aliveCount > 1) return false; // Early exit
    }
    return aliveCount <= 1;
}

void Board::runSimulation() {
    std::ofstream logFile("simulation.log");

    if (!logFile) {
        std::cerr << "Error: Failed to open simulation.log for writing.\n";
        return; // Exit early to avoid silent failures
    }

    while (!isGameOver()) {
        tap();
        displayAllBugs();

        for (const Crawler* bug : crawlers) {
            logFile << "ID: " << bug->getId()
                    << " Position: (" << bug->getPositionX() << "," << bug->getPositionY() << ")"
                    << " Size: " << bug->getSize()
                    << " Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
            if (!logFile) {
                std::cerr << "Error writing to log file!\n";
                break;
            }
        }
        logFile.flush(); // Ensure data is written even if program crashes later

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    logFile.close();
}

void Board::handleFights() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            auto& bugsInCell = cells[{x, y}];

            // skip cells with 0 or 1 bug - no fights
            if (bugsInCell.size() <= 1) {
                continue;
            }

            // count alive bugs
            std::vector<Crawler*> aliveBugs;
            for (Crawler* bug : bugsInCell) {
                if (bug->isAlive()) {
                    aliveBugs.push_back(bug);
                }
            }

            // skip if less than two bugs alive
            if (aliveBugs.size() <= 1) {
                continue;
            }

            // find the bugs with max size
            int maxSize = 0;
            std::vector<Crawler*> largestBugs;

            for (Crawler* bug : aliveBugs) {
                if (bug->getSize() > maxSize) {
                    maxSize = bug->getSize();
                    largestBugs.clear();
                    largestBugs.push_back(bug);
                } else if (bug->getSize() == maxSize) {
                    largestBugs.push_back(bug);
                }
            }


            Crawler* winner;
            if (largestBugs.size() > 1) {
                // pick random bug
                int randomIndex = rand() % largestBugs.size();
                winner = largestBugs[randomIndex];
            } else {
                winner = largestBugs[0];
            }


            int sizeGain = 0;
            for (Crawler* bug : aliveBugs) {
                if (bug != winner) {
                    sizeGain += bug->getSize();
                    bug->setAlive(false);


                    eatenBy[bug->getId()] = winner->getId();

                    std::cout << "Bug " << winner->getId() << " ate bug " << bug->getId()
                              << " at position (" << x << "," << y << ")" << std::endl;
                }
            }


            if (sizeGain > 0) {
                winner->increaseSize(sizeGain);
                std::cout << "Bug " << winner->getId() << " grew to size "
                          << winner->getSize() << std::endl;
            }
        }
    }
}

void Board::updateCells() {

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cells[{x, y}].clear();
        }
    }

    for (Crawler* bug : crawlers) {
        if (bug->isAlive()) {
            Position pos = {bug->getPositionX(), bug->getPositionY()};
            cells[{pos.x, pos.y}].push_back(bug);
        }
    }
}

