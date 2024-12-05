#include "Node.hpp"

// Constructor
Node::Node(int keyValue) : key(keyValue), prev(nullptr), next(nullptr) {}

// Virtual Destructor
Node::~Node() {}
