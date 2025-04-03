//
// Created by Siew Yahuai on 29/03/2025.
//

#include <iostream>
#include "Board.h"
using namespace std;

Board board;

void displayMenu(){
    cout << "1. Initialise Bug Board"
         << "\n2. Display all Bugs"
         << "\n3. Find a Bug"
         << "\n4. Tap the Bug Board"
         << "\n5. Display Life History of all Bugs"
         << "\n6. Display all Cells listing their Bugs"
         << "\n7. Run simulation"
         << "\n8. Exit" << endl;
}

int main(){
    int choice;
    bool initialized = false;

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
                board.initializeBoard("crawler-bugs.txt");
                initialized = true;
                cout << "Board initialized!\n";
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                cout << "Exiting..." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }while(choice != 8);
    return 0;
}