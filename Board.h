//
// Created by plo on 02/04/2025.
//


#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include <list>
#include <string>
#include <map>
#include "Crawler.h"



class Board {

  private:
    std::vector<Crawler*> crawlers;

    std::map<std::pair<int, int>, std::vector<Crawler*> > cells;
    bool gameOver;

    void updateCells();
    void handleFights();
    bool isOnlyOneBugAlive() const;

    public:
     Board();
     ~Board();

     void initializeBoard(const std::string& filename);

     bool loadBugsFromFile(std::string& fileName);

     void displayAllBugs() const;

     Crawler* findBug(int id) const;

     void tap();

     void displayLifeHistory() const;

     void displayAllCells() const;

     void runSimulation();

    void writeHistoryToFile(const std::string& filename) const;

};



#endif //BOARD_H
