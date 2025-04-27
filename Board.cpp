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
            cells[{i, j}] = std::vector<Bug*>();
        }
    }
}

Board::~Board() {
    for (auto bug : bugs) {
        delete bug;
    }
    bugs.clear();
    cells.clear();
}

void Board::updateCells() {
    // Clear existing cells
    for (auto& cell : cells) {
        cell.second.clear();
    }

    // Update cells with alive crawlers
    for (Bug* bug : bugs) {
        if (bug->isAlive()) {
            int x = bug->getPositionX();
            int y = bug->getPositionY();
            cells[{x, y}].push_back(bug);
        }
    }
}

void Board::handleFights() {
    for (auto& cellEntry : cells) {
        auto& bugsInCell = cellEntry.second;
        if (bugsInCell.size() <= 1) continue;

        int maxSize = 0;
        for (Bug* bug : bugsInCell) {
            if (bug->getSize() > maxSize) {
                maxSize = bug->getSize();
            }
        }

        // Collect contenders of max size
        std::vector<Bug*> contenders;
        for (Bug* bug : bugsInCell) {
            if (bug->getSize() == maxSize) {
                contenders.push_back(bug);
            }
        }

        // Randomly select a winner if multiple contenders
        Bug* winner = contenders[rand() % contenders.size()];
        int totalSizeEaten = 0;

        // Kill other bugs and update winner's size
        for (Bug* bug : bugsInCell) {
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
            bugs.push_back(new Crawler(id, x, y, dir, size));
        } else if (type == 'H') {
            bugs.push_back(new Hopper(id, x, y, dir, size));
        } else {
            std::cerr << "Unknown bug type: " << type << std::endl;
        }
    }
    file.close();
    updateCells(); // Update positions
}



//(2) DisplayAllBugs();
void Board::displayAllBugs() const {
    std::cout << "\n--- All Bugs ---\n";
    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(10) << "Type"
              << std::setw(10) << "Location"
              << std::setw(8) << "Size"
              << std::setw(10) << "Direction"
              << std::setw(10) << "HopLength"
              << "Status\n";
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& bug : bugs) {
        // Get direction as string
        std::string directionStr;
        switch (bug->getDirection()) {
            case Direction::North: directionStr = "North"; break;
            case Direction::East:  directionStr = "East";  break;
            case Direction::South: directionStr = "South"; break;
            case Direction::West:  directionStr = "West";  break;
            default: directionStr = "Unknown";
        }

        // Get bug type and hop length if applicable
        std::string bugType;
        std::string hopLengthStr = "-"; // Default for non-hoppers

        if (dynamic_cast<const Crawler*>(bug) != nullptr) {
            bugType = "Crawler";
        } else if (const auto* hopper = dynamic_cast<const Hopper*>(bug)) {
            bugType = "Hopper";
            hopLengthStr = std::to_string(hopper->getHopLength());
        } else {
            bugType = "Unknown";
        }

        std::cout << std::left
                  << std::setw(6) << bug->getId()
                  << std::setw(10) << bugType
                  << "(" << bug->getPositionX() << "," << bug->getPositionY() << ")"
                  << std::setw(4) << " "
                  << std::setw(8) << bug->getSize()
                  << std::setw(10) << directionStr
                  << std::setw(10) << hopLengthStr
                  << (bug->isAlive() ? "Alive" : "Dead")
                  << std::endl;
    }
}


void Board::tap() {
    std::cout << "\nTapping the bug board...\n";

  for(Bug* bug : bugs) {
    if(bug->isAlive()) {
      bug->move();
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
                // Check if there are any alive bugs in this cell
                bool hasAliveBugs = false;
                for (const Bug* bug : it->second) {
                    if (bug->isAlive()) {
                        hasAliveBugs = true;
                        break;
                    }
                }

                if (hasAliveBugs) {
                    bool first = true;
                    for (const Bug* bug : it->second) {
                        if (bug->isAlive()) {  // only display alive bugs
                            if (!first) {
                                std::cout << ", ";
                            }

                            // determine bug type
                            std::string bugType = "Unknown";
                            if (dynamic_cast<const Crawler*>(bug) != nullptr) {
                                bugType = "Crawler";
                            } else if (dynamic_cast<const Hopper*>(bug) != nullptr) {
                                bugType = "Hopper";
                            }

                            std::cout << bugType << " " << bug->getId();
                            first = false;
                        }
                    }
                } else {
                    std::cout << "empty";
                }
            } else {
                std::cout << "empty";
            }
            std::cout << std::endl;
        }
    }
}

Bug* Board::findBug(int id) const {
    for (Bug* bug : bugs) {
        if (bug->getId() == id) {
            return bug;
        }
    }
    return nullptr; // if not found
}

void Board::displayLifeHistory() const {
    for (const Bug* bug : bugs) {

        std::string bugType = "Unknown";
        if (dynamic_cast<const Crawler*>(bug) != nullptr) {
            bugType = "Crawler";
        } else if (dynamic_cast<const Hopper*>(bug) != nullptr) {
            bugType = "Hopper";
        }

        std::cout << bug->getId() << " " << bugType << " Path: ";
        bool first = true;
        for (const Position& pos : bug->getPath()) {
            if (!first) std::cout << ",";
            std::cout << "(" << pos.x << "," << pos.y << ")";
            first = false;
        }
        if (!bug->isAlive()) {
            std::cout << " Eaten by " << bug->getKilledBy();
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

    for (const Bug* bug : bugs) {

        std::string bugType = "Unknown";
        if (dynamic_cast<const Crawler*>(bug) != nullptr) {
            bugType = "Crawler";
        } else if (dynamic_cast<const Hopper*>(bug) != nullptr) {
            bugType = "Hopper";
        }

        file << bug->getId() << " " << bugType << " Path: ";
        bool first = true;
        for (const Position& pos : bug->getPath()) {
            if (!first) file << ",";
            file << "(" << pos.x << "," << pos.y << ")";
            first = false;
        }
        if (!bug->isAlive()) {
            file << " Eaten by " << bug->getKilledBy();
        }
        file << std::endl;
    }

    file.close();
    std::cout << "Life history written to " << filename << std::endl;
}

bool Board::isGameOver() const {
    int aliveCount = 0;
    for (const Bug* bug : bugs) {
        if (bug->isAlive()) aliveCount++;
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

        for (const Bug* bug : bugs) {
            logFile << "ID: " << bug->getId()
                    << " Position: (" << bug->getPositionX() << "," << bug->getPositionY() << ")"
                    << " Size: " << bug->getSize()
                    << " Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
            if (!logFile) {
                std::cerr << "Error writing to log file!\n";
                break;
            }
        }
        logFile.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    logFile.close();
}
