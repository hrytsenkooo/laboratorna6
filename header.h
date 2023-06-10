#pragma once
#include <iostream>

template <typename KeyType, typename ValueType>
class Node {
public:
    KeyType key;
    ValueType value;

    Node() : key(), value() {}
    Node(const KeyType& k, const ValueType& v) : key(k), value(v) {}
};

template<typename KeyType, typename ValueType>
class HashTable {
public:
    int count;
private:
    int TABLE_SIZE;
    Node<KeyType, ValueType>* table;

public:
    HashTable(int size) : TABLE_SIZE(size), count(0) {
        table = new Node<KeyType, ValueType>[TABLE_SIZE]();
    }

    ~HashTable() {
        delete[] table;
    }

    int hash(const KeyType& key) {
        std::hash<KeyType> hasher;
        return hasher(key) % TABLE_SIZE;
    }

    void insert(const KeyType& key, const ValueType& value) {
        if (count == TABLE_SIZE) {
            throw std::runtime_error("Table is full. Cannot insert more elements.");
        }

        int index = hash(key);

        while (table[index].key != KeyType()) {
            if (table[index].key == key) {
                throw std::runtime_error("Element with the same key alredy exists in the table.");
            }

            index = (index + 1) % TABLE_SIZE;
            if (index == hash(key)) {
                throw std::runtime_error("Table is full. Cannot insert more elements.");
            }
        }

        table[index] = Node<KeyType, ValueType>(key, value);
        count++;
    }

    ValueType* search(const KeyType& key) {
        int index = hash(key);

        int iterations = 0;
        while (table[index].key != KeyType()) {
            if (table[index].key == key) {
                return &table[index].value;
            }

            iterations++;

            index = (index + 1) % TABLE_SIZE;

            if (iterations > TABLE_SIZE) {
                throw std::runtime_error("Key not found.");
            }
        }

        return nullptr;
    }

    void remove(const KeyType& key) {

        int index = hash(key);

        int iterations = 0;
        while (table[index].key != KeyType()) {
            if (table[index].key == key) {
                table[index].key = KeyType();
                count--;
                return;
            }

            index = (index + 1) % TABLE_SIZE;

            iterations++;

            if (iterations >= TABLE_SIZE) {
                throw std::runtime_error("Key not found.");
            }
        }

        throw std::runtime_error("Key not found.");
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].key = KeyType();
        }
        count = 0;
    }

    // Iterator class for iterating over the hash table elements
    class Iterator {
    private:
        HashTable<KeyType, ValueType>& hashTable;
        int index;

    public:
        Iterator(HashTable<KeyType, ValueType>& ht) : hashTable(ht), index(0) {}

        void begin() {
            index = 0;
            while (index < hashTable.TABLE_SIZE && hashTable.table[index].key == KeyType()) {
                index++;
            }
        }

        bool end() {
            return index >= hashTable.TABLE_SIZE;
        }

        Node<KeyType, ValueType>& operator*() {
            return hashTable.table[index];
        }

        void operator++() {
            index++;
            while (index < hashTable.TABLE_SIZE && hashTable.table[index].key == KeyType()) {
                index++;
            }
        }
    };

    int size() const {
        return TABLE_SIZE;
    }
};

template <typename KeyType, typename ValueType>
void performOperations(HashTable<KeyType, ValueType>& hashTable, int size) {
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            if (hashTable.count == size) {
                std::cout << "Table is full. Cannot insert more elements." << std::endl;
                break;
            }

            int numElements;
            std::cout << "Enter the number of elements to insert: ";
            std::cin >> numElements;
            if (numElements > size) {
                std::cout << "Too many elements to insert" << std::endl;
                break;
            }
            else if (hashTable.count + numElements > size) {
                std::cout << "Too many elements to insert" << std::endl;
                break;
            }

            int counts = 0;
            while (counts < numElements) {
                std::cout << "Enter the key: ";
                KeyType key;
                std::cin >> key;
                std::cout << "Enter the value: ";
                ValueType value;
                std::cin >> value;
                hashTable.insert(key, value);
                counts++;
            }
            std::cout << "Elements inserted." << std::endl;
            break;
        }
        case 2:
            hashTable.clear();
            std::cout << "Table cleared." << std::endl;
            break;
        case 3: {
            std::cout << "Enter the key to search: ";
            KeyType key;
            std::cin >> key;
            ValueType* value = hashTable.search(key);
            if (value != nullptr) {
                std::cout << "Value found: " << *value << std::endl;
            }
            else {
                std::cout << "Value not found." << std::endl;
            }
            break;
        }
        case 4: {
            if (hashTable.count == 0) {
                std::cout << "The table is completely empty." << std::endl;
                break;
            }
            std::cout << "Enter the key to delete: ";
            KeyType key;
            std::cin >> key;
            try {
                hashTable.remove(key);
                std::cout << "Key deleted." << std::endl;
            }
            catch (const std::runtime_error& error) {
                std::cout << error.what() << std::endl;
            }
            break;
        }
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    } while (choice != 0);
}
