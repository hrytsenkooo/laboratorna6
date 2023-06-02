#include "header.h"

int main() {

    std::cout << "Enter the size of the table: ";
    int size;
    std::cin >> size;

    HashTable<std::string> table(size);


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
                std::cout << "Too much elements" << std::endl;
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

                try {
                    table.insert(key, value);
                    count++;
                }
                catch (std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            std::cout << "Elements inserted." << std::endl;
            break;
        }
        case 2: {
            if (table.iterator().hasNext()) {
                table = HashTable<std::string>(size);
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
                catch (std::runtime_error& e) {
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
