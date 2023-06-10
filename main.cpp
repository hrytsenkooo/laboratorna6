#include "funcs.h"
#include "header.h"

int main() {
    std::cout << "Enter the size of the table: ";
    int size;
    std::cin >> size;

    std::cout << "Enter type of data for hash table\n1 - int\n2 - string\n3 - double\nYour choice: ";
    int dataChoice;
    std::cin >> dataChoice;

    switch (dataChoice) {
    case 1: {
        HashTable<int, std::string> hashTable(size);
        // Use int as the key and string as the value type
        performOperations(hashTable, size); 
        break;
    }
    case 2: {
        HashTable<std::string, std::string> hashTable(size);
        // Use string as the key type and string as the value type
        performOperations(hashTable, size);  
        break;
    }
    case 3: {
        HashTable<double, std::string> hashTable(size);
        // Use double as the key type and string as the value type
        performOperations(hashTable, size);  
        break;
    }
    default:
        std::cout << "Invalid choice." << std::endl;
        return 0;
    }

    return 0;
}
