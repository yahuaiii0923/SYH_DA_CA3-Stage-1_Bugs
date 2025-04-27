//
// Created by Siew Yahuai on 29/03/2025.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Board.h"
using namespace std;

Board board;

void displayMenu(){
    cout << "1. Initialise Bug Board"
         << "\n2. Display all Bugs"
         << "\n3. Find a Bug By Id"
         << "\n4. Tap the Bug Board"
         << "\n5. Display Life History of all Bugs"
         << "\n6. Display all Cells listing their Bugs"
         << "\n7. Run simulation"
         << "\n8. Exit" << endl;

}

int main(){
    int choice;
    bool initialized = false;
    srand(time(NULL));

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice != 1 && choice != 8 && !initialized) {
            cout << "Board not initialized. Please select option 1 first.\n";
            continue;
        }

        switch(choice) {
            case 1:
                board.initializeBoard("bugs.txt");
                initialized = true;
                cout << "Board initialized!\n";
                break;
            case 2:
                board.displayAllBugs();
                break;
            case 3: {
                int searchId;
                cout << "Enter bug ID to search: ";

                // Validate input is a number
                while (!(cin >> searchId)) {
                    cout << "Invalid input. Please enter a numeric bug ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                Bug *foundBug = board.findBug(searchId);

                if (foundBug != nullptr) {
                    // Get bug type
                    string bugType = "Unknown";
                    if (dynamic_cast<const Crawler *>(foundBug) != nullptr) {
                        bugType = "Crawler";
                    } else if (dynamic_cast<const Hopper *>(foundBug) != nullptr) {
                        bugType = "Hopper";
                    }

                    // Get direction as string
                    string directionStr;
                    switch (foundBug->getDirection()) {
                        case Direction::North: directionStr = "North";
                            break;
                        case Direction::East: directionStr = "East";
                            break;
                        case Direction::South: directionStr = "South";
                            break;
                        case Direction::West: directionStr = "West";
                            break;
                        default: directionStr = "Unknown";
                    }

                    // Display bug details
                    cout << "\n--- Bug Found ---\n";
                    cout << "ID: " << foundBug->getId() << "\n";
                    cout << "Type: " << bugType << "\n";
                    cout << "Location: (" << foundBug->getPositionX() << ", "
                            << foundBug->getPositionY() << ")\n";
                    cout << "Size: " << foundBug->getSize() << "\n";
                    cout << "Direction: " << directionStr << "\n";

                    // Show hop length if it's a Hopper
                    if (const Hopper *hopper = dynamic_cast<const Hopper *>(foundBug)) {
                        cout << "Hop Length: " << hopper->getHopLength() << "\n";
                    }

                    cout << "Status: " << (foundBug->isAlive() ? "Alive" : "Dead") << "\n";

                    // Show killer if dead
                    if (!foundBug->isAlive()) {
                        cout << "Killed by: Bug " << foundBug->getKilledBy() << "\n";
                    }
                } else {
                    cout << "Bug " << searchId << " not found.\n";
                }
                break;
            }
            case 4:
                board.tap();
                break;
            case 5:
                board.displayLifeHistory();
                break;
            case 6:
                board.displayAllCells();
                break;
            case 7:
                board.runSimulation();
                break;
            case 8: {
                auto now = std::chrono::system_clock::now();
                std::time_t now_time = std::chrono::system_clock::to_time_t(now);
                std::tm* now_tm = std::localtime(&now_time);
                std::stringstream ss;
                ss << "bugs_life_history_"
                   << std::put_time(now_tm, "%Y%m%d_%H%M%S") << ".out";
                board.writeHistoryToFile(ss.str());
                std::cout << "Exiting..." << std::endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }while(choice != 8);
    return 0;
}