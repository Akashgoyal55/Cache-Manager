#include "HashTable.hpp"
#include <iostream>

// Default constructor
HashTable::HashTable() {
    table = new HashNode*[_HASH_TABLE_SIZE]();
    numberOfItems = 0;
}

// Method to return the hash table array
HashNode** HashTable::getTable() {
    return table;
}

// Method to return the size of the hash table
int HashTable::getSize() {
    return _HASH_TABLE_SIZE;
}

// Method to check if the hash table is empty
bool HashTable::isEmpty() {
    return numberOfItems == 0;
}

// Method to get the number of items in the hash table
int HashTable::getNumberOfItems() {
    return numberOfItems;
}

// Method to add a new item to the hash table
bool HashTable::add(int searchKey, HashNode* newItem) {
    int index = searchKey % _HASH_TABLE_SIZE; // Calculate index
    HashNode* current = static_cast<HashNode*>(table[index]);

    while (current != nullptr) {
        if (current->key == searchKey) {
            // Key already exists
            return false;
        }
        current = static_cast<HashNode*>(current->next);
    }

    newItem->next = table[index];
    if (table[index] != nullptr) {
        table[index]->prev = newItem;
    }
    table[index] = newItem;

    numberOfItems++;
    return true;
}

// Method to remove an item from the hash table
bool HashTable::remove(int searchKey) {
    int index = searchKey % _HASH_TABLE_SIZE; // Calculate index
    HashNode* current = static_cast<HashNode*>(table[index]);

    while (current != nullptr) {
        if (current->key == searchKey) {
            // Found the node to remove
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                table[index] = static_cast<HashNode*>(current->next); // Update head
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }

            delete current;
            numberOfItems--;
            return true;
        }
        current = static_cast<HashNode*>(current->next);
    }

    return false; // Key not found
}

// Method to clear all items from the hash table
void HashTable::clear() {
    for (int i = 0; i < _HASH_TABLE_SIZE; ++i) {
        HashNode* current = static_cast<HashNode*>(table[i]);
        while (current != nullptr) {
            HashNode* toDelete = current;
            current = static_cast<HashNode*>(current->next);
            delete toDelete;
        }
        table[i] = nullptr;
    }
    numberOfItems = 0;
}

// Method to get an item by its search key
HashNode* HashTable::getItem(int searchKey) {
    int index = searchKey % _HASH_TABLE_SIZE; // Calculate index
    HashNode* current = static_cast<HashNode*>(table[index]);

    while (current != nullptr) {
        if (current->key == searchKey) {
            return current; // Item found
        }
        current = static_cast<HashNode*>(current->next);
    }

    return nullptr; // Item not found
}

// Method to check if an item with the given search key exists
bool HashTable::contains(int searchKey) {
    return getItem(searchKey) != nullptr;
}

