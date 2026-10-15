#include "LeaveSystem.h"
#include <iostream>
#include <limits>
#include <exception>

void showMenu() {
    std::cout << "\n====================================\n";
    std::cout << "      FACULTY LEAVE MANAGEMENT\n";
    std::cout << "====================================\n";
    std::cout << "1. Add Record\n";
    std::cout << "2. Display Records\n";
    std::cout << "3. Search Record\n";
    std::cout << "4. Update Record\n";
    std::cout << "5. Delete Record\n";
    std::cout << "6. Main Transaction / Process\n";
    std::cout << "7. Report\n";
    std::cout << "8. Save / Load\n";
    std::cout << "9. Exit\n";
}

int main() {
    try {
        LeaveSystem system;
        try {
            system.loadData();
        } catch (const std::exception& error) {
            std::cout << "Could not load saved data: " << error.what() << '\n';
            std::cout << "Check the files in the Data folder before restarting.\n";
            return 1;
        }

        int choice = 0;
        while (choice != 9) {
            showMenu();
            std::cout << "Enter your choice: ";
            if (!(std::cin >> choice)) {
                std::cout << "Invalid input. Enter a number from 1 to 9.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            std::cin.ignore(10000, '\n');

            try {
                if (choice == 1) system.addRecord();
                else if (choice == 2) system.displayRecords();
                else if (choice == 3) system.searchRecord();
                else if (choice == 4) system.updateRecord();
                else if (choice == 5) system.deleteRecord();
                else if (choice == 6) system.processTransaction();
                else if (choice == 7) system.report();
                else if (choice == 8) system.saveLoadMenu();
                else if (choice == 9) {
                    system.saveNow();
                    std::cout << "Goodbye.\n";
                } else {
                    std::cout << "Invalid menu choice. Enter 1 to 9.\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Operation failed: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cout << "Program could not start: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
