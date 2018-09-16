//
// Created by michael on 18-9-11.
//

#include <iostream>
#include "Node.h"

void Node::print() {
    std::cout << value << std::endl;
}

int Node::NODE_TYPE_LEFT = 0;
int Node::NODE_TYPE_RIGHT = 1;
int Node::NODE_TYPE_ROOT = 2;
int Node::NODE_TYPE_UNKNOWN = -1;

Node::Node(int value, int type):
        value(value),
        nodeType(type),
        factor(0) {
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    delete(left);
    delete(right);
//    std::cout << "Delete node: " << value << std::endl;
}

bool Node::isLeaf() {
    return left == nullptr && right == nullptr;
}
