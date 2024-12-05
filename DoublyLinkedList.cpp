#include "DoublyLinkedList.hpp"
#include <iostream>

// Default constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Get the head of the list
Node* DoublyLinkedList::getHead() {
    return head;
}

// Insert a node at the head
void DoublyLinkedList::insertAtHead(Node* newNode) {
    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
        tail = head;
    }
}

// Insert a node at the tail
void DoublyLinkedList::insertAtTail(Node* newNode) {
    newNode->next = nullptr;
    newNode->prev = tail;
    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == nullptr) {
        head = tail;
    }
}

// Move a node to the head of the list
void DoublyLinkedList::moveToHead(Node* existingNode) {
    if (existingNode == head) {
        return; // Already at the head
    }
    if (existingNode->prev != nullptr) {
        existingNode->prev->next = existingNode->next;
    }
    if (existingNode->next != nullptr) {
        existingNode->next->prev = existingNode->prev;
    }
    if (existingNode == tail) {
        tail = existingNode->prev;
    }
    existingNode->next = head;
    existingNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = existingNode;
    }
    head = existingNode;
}

// Delete the tail node
void DoublyLinkedList::deleteTailNode() {
    if (tail == nullptr) {
        return; // List is empty
    }
    if (tail->prev != nullptr) {
        tail->prev->next = nullptr;
    } else {
        head = nullptr; // List becomes empty
    }
    Node* temp = tail;
    tail = tail->prev;
    delete temp;
}

// Delete a specific node
void DoublyLinkedList::deleteNode(Node* existingNode) {
    if (existingNode == nullptr) {
        return;
    }
    if (existingNode->prev != nullptr) {
        existingNode->prev->next = existingNode->next;
    } else {
        head = existingNode->next;
    }
    if (existingNode->next != nullptr) {
        existingNode->next->prev = existingNode->prev;
    } else {
        tail = existingNode->prev;
    }
    delete existingNode;
}

// Delete the entire list
void DoublyLinkedList::deleteList() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
}

