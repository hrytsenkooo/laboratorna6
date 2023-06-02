#pragma once
#include <iostream>
#include <string>

template<class T>
class HashTable {
private:
    int size;
    T* data;
    int* keys;
    bool* used;

    int hash(int key);

public:
    HashTable(int size);

    ~HashTable();

    void insert(int key, T element);

    T search(int key);

    void remove(int key);

    class Iterator {
    private:
        T* current;
        int* keys;
        bool* used;
        int index;
        int size;

    public:
        Iterator(T* data, int* keys, bool* used, int size);

        bool hasNext();

        T next();

        int getKey();
    };

    Iterator iterator();
};

void displayMenu();
