//
// Created by plo on 02/04/2025.
//


#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include <list>
#include <string>
#include <map>
#include "Bug.h"
#include "Crawler.h"
#include "Jumper.h"


class Board {
private:
    std::vector<Bug *> bugs; // changed from std::vector<Crawler*> to store any bug type
    std::map<std::pair<int, int>, std::vector<Bug*>> cells;
    bool gameOver;


    void updateCells();

    void handleFights();

    bool isOnlyOneBugAlive() const;

public:
    Board();

    ~Board();

    bool loadBugsFromFile(std::string &fileName);

    void initializeBoard(const std::string &filename);

    void displayAllBugs() const;

    Bug *findBug(int id) const;

    void tap();

    void displayLifeHistory() const;

    void displayAllCells() const;

    void runSimulation();

    void writeHistoryToFile(const std::string &filename) const;

    bool isGameOver() const;
};


#endif //BOARD_H
