#include "FifoNode.hpp"

// Constructor for Data
Data::Data(int keyValue, std::string fullName, std::string address, std::string city, std::string state, std::string zip)
    : key(keyValue), fullName(fullName), address(address), city(city), state(state), zip(zip) {}

// Constructor for FifoNode
FifoNode::FifoNode(int value) : Node(value), dataValues(nullptr) {}
