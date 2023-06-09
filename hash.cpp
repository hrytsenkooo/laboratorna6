#include "header.h"

template<class T>
int HashTable<T>::hash(int key) {
    return key % size;
}

template<class T>
HashTable<T>::HashTable(int size) {
    this->size = size;
    data = new T[size];
    keys = new int[size];
    used = new bool[size];
    for (int i = 0; i < size; i++) {
        used[i] = false;
    }
}

template<class T>
HashTable<T>::~HashTable() {
    delete[] data;
    delete[] keys;
    delete[] used;
}

template<class T>
void HashTable<T>::insert(int key, T element) {
    if (count == size) {
        throw std::runtime_error("Table is full. Cannot insert more elements.");
    }

    int index = hash(key);
    while (used[index]) {
        if (keys[index] == key) {
            throw std::runtime_error("Element with the same key already exists in the table.");
        }
        index = (index + 1) % size;
    } 

    keys[index] = key;
    data[index] = element;
    used[index] = true;
    count++;
}

template<class T>
T HashTable<T>::search(int key) {
    int index = hash(key);
    int iterations = 0;
    while (used[index]) {
        if (keys[index] == key) {
            return data[index];
        }
        index = (index + 1) % size;
        iterations++;
        if (iterations > size) {
            throw std::runtime_error("Key not found.");
        }
    }
    throw std::runtime_error("Key not found.");
}

template<class T>
void HashTable<T>::remove(int key) {
    int index = hash(key);
    while (used[index]) {
        if (keys[index] == key) {
            used[index] = false;
            count--;
            return;
        }
        index = (index + 1) % size;
    }
    throw std::runtime_error("Key not found.");
}

template<class T>
void HashTable<T>::clear() {
    for (int i = 0; i < size; i++) {
        used[i] = false;
    }
    count = 0;
}
template<class T>
HashTable<T>::Iterator::Iterator(T* data, int* keys, bool* used, int size) {
    this->current = data;
    this->keys = keys;
    this->used = used;
    this->index = 0;
    this->size = size;
}

template<class T>
bool HashTable<T>::Iterator::hasNext() {
    while (index < size && !used[index]) {
        index++;
    }
    return index < size;
}

template<class T>
T HashTable<T>::Iterator::next() {
    T element = *current;
    current++;
    index++;
    while (index < size && !used[index]) {
        index++;
    }
    return element;
}

template<class T>
int HashTable<T>::Iterator::getKey() {
    return keys[index];
}

template<class T>
typename HashTable<T>::Iterator HashTable<T>::iterator() {
    return Iterator(data, keys, used, size);
}

template class HashTable<std::string>;

void displayMenu() {
    std::cout << "\n===== Menu =====" << std::endl;
    std::cout << "1) Insert an element" << std::endl;
    std::cout << "2) Clear the table" << std::endl;
    std::cout << "3) Search for an element by key" << std::endl;
    std::cout << "4) Delete an element by key" << std::endl;
    std::cout << "0) Exit" << std::endl;
    std::cout << "================\n" << std::endl;
}

template class HashTable<int>;
template class HashTable<double>;
template class HashTable<std::string>;
