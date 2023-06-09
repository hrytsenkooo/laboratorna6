#include "header.h"

int main() {

    std::cout << "Enter the size of the table: ";
    int size;
    std::cin >> size;

    std::cout << "Enter the type of data (1 for int, 2 for double, 3 for string): ";
    int datachoice;
    std::cin >> datachoice;

    HashTable<std::string> table(size);
    if (datachoice == 1) {
        HashTable<int> table(size);
    }
    else if (datachoice == 2) {
        HashTable<double> table(size);
    }
    else if (datachoice == 3) {
        HashTable<std::string> table(size);
    }
    else {
        std::cout << "Invalid data type choice. " << std::endl;
        return 0;
    }


    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int numElements;
            std::cout << "Enter the number of elements to insert: ";
            std::cin >> numElements;
            if (numElements > size) {
                std::cout << "Too much elements to insert" << std::endl;
                break;
            }
            else if (table.count == size) {
                std::cout << "Table is full. Cannot insert more elements." << std::endl;
                break;
            }

            int count = 0;
            while (count < numElements) {
                int key;
                std::string value;
                std::cout << "Enter a key: ";
                std::cin >> key;
                std::cout << "Enter a value: ";
                std::cin.ignore();
                std::getline(std::cin, value);
                table.insert(key, value);
                count++;
            }

            std::cout << "Elements inserted." << std::endl;
            break;
        }
        case 2: {
            if (table.iterator().hasNext()) {
                table.clear();
                std::cout << "Table cleared." << std::endl;
            }
            else {
                std::cout << "Table is already empty." << std::endl;
            }
            break;
        }
        case 3: {
            if (table.iterator().hasNext()) {
                int searchKey;
                std::cout << "Enter the key to search for: ";
                std::cin >> searchKey;
                try {
                    std::string searchResult = table.search(searchKey);
                    std::cout << "Search result: " << searchResult << std::endl;
                }
                catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else {
                std::cout << "Table is empty. Cannot search for an element." << std::endl;
            }
            break;
        }
        case 4: {
            if (table.iterator().hasNext()) {
                int removeKey;
                std::cout << "Enter the key to remove: ";
                std::cin >> removeKey;
                try {
                    table.remove(removeKey);
                    std::cout << "Element with key " << removeKey << " removed." << std::endl;
                }
                catch (std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else {
                std::cout << "Table is empty. Cannot delete an element." << std::endl;
            }
            break;
        }
        case 0: {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
