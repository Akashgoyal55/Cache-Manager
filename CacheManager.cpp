#include "CacheManager.hpp"

/**
 * CacheManager Constructor
 */
CacheManager::CacheManager(size_t capacity) {
    _maxSize = capacity;
    _curSize = 0;
    _fifoCache = new DoublyLinkedList();
    _hashTable = new HashTable();
}

/**
 * Getter for _fifoCache
 */
DoublyLinkedList* CacheManager::getFifoList() {
    return _fifoCache;
}

/**
 * Getter for _hashTable
 */
HashTable* CacheManager::getTable() {
    return _hashTable;
}

/**
 * Add an item to the cache
 */
bool CacheManager::add(int key, Data* newItem) {
    // Check if the key already exists
    if (_hashTable->contains(key)) {
        Node* existingNode = static_cast<Node*>(_hashTable->getItem(key)->cacheNode);
        _fifoCache->moveToHead(existingNode);
        return false;
    }

    // If the cache is full, remove the tail node
    if (_curSize == _maxSize) {
        Node* tailNode = _fifoCache->getHead();
        if (tailNode) {
            _fifoCache->deleteTailNode();
            _hashTable->remove(tailNode->key);
            delete tailNode;
            _curSize--;
        }
    }

    // Add a new node to the FIFO list
    FifoNode* newNode = new FifoNode(key);
    newNode->dataValues = newItem; // Directly set data values
    _fifoCache->insertAtHead(newNode);

    // Add a new node to the hash table
    HashNode* hashNode = new HashNode(key);
    hashNode->cacheNode = newNode; // Directly set the cache node
    _hashTable->add(key, hashNode);

    _curSize++;
    return true;
}

/**
 * Remove an item from the cache
 */
bool CacheManager::remove(int key) {
    if (!_hashTable->contains(key)) {
        return false;
    }

    HashNode* hashNode = _hashTable->getItem(key);
    if (hashNode && hashNode->cacheNode) {
        _fifoCache->deleteNode(static_cast<Node*>(hashNode->cacheNode));
        delete static_cast<Node*>(hashNode->cacheNode); // Safely delete the associated FIFO node
    }

    _hashTable->remove(key);
    return true;
}

/**
 * Clear the cache
 */
void CacheManager::clear() {
    _fifoCache->deleteList();
    _hashTable->clear();
    _curSize = 0;
}

/**
 * Get the number of items in the cache
 */
size_t CacheManager::getNumberOfItems() {
    return _curSize;
}

/**
 * Check if the cache is empty
 */
bool CacheManager::isEmpty() {
    return _curSize == 0;
}

/**
 * CacheManager Destructor
 */
CacheManager::~CacheManager() {
    clear();
    delete _fifoCache;
    delete _hashTable;
}
