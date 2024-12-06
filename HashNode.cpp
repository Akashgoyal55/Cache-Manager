/**
*
* HashNode.cpp : This is the implementation file for Hash Node.
*
* 11/27/24 - Created by ChatGpt
* 11/27/24 - Modified by Chirayu Jain and Akash Goyal
* 
*/

#include "HashNode.hpp"

HashNode::HashNode(int value) : Node(value), cacheNode(nullptr) {}

Node* HashNode::getCacheNode() const {
    return cacheNode;
}

void HashNode::setCacheNode(Node* node) {
    cacheNode = node;
}