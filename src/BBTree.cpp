//
// Created by michael on 18-9-11.
//

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <stack>
#include <iostream>
#include <queue>
#include <map>
#include "BBTree.h"

BBTree::BBTree(): root(nullptr), depth(0) {}

void BBTree::insert(Node *parent, const int &value) {
    if (parent->value > value) {
        if (parent->left) insert(parent->left, value);
        else insertNode(parent, new Node(value, Node::NODE_TYPE_LEFT));
    } else {
        if (parent->right) insert(parent->right, value);
        else insertNode(parent, new Node(value, Node::NODE_TYPE_RIGHT));
    }
}

void BBTree::insertNode(Node *root, Node *node) {
    assert(root);
    assert(node->nodeType == Node::NODE_TYPE_LEFT || node->nodeType == Node::NODE_TYPE_RIGHT);
    assert((node->nodeType == Node::NODE_TYPE_RIGHT ? root->right : root->left) == nullptr);

    node->parent = root;

    auto factor = this->root->factor;

    if (node->nodeType == Node::NODE_TYPE_LEFT) {
        assert(!(node->left));

        root->left = node;

        if (root->factor == 0) {
            root->factor = 1;
        } else if (root->factor == -1) {
            root->factor = 0;
        }
    } else {
        assert(!(root->right));

        root->right = node;

        if (root->factor == 0) {
            root->factor = -1;
        } else if (root->factor == 1) {
            root->factor = 0;
        }
    }

    balanceTree(root);

    if (factor == 0 && abs(this->root->factor) > 0) {
        depth += 1;
    }
}

void BBTree::balanceTree(Node *root) {
    auto parent = root->parent;
    auto child = root;

    while (parent) {
        if (parent->factor > 0 && child->factor > 0) {
            if (!(parent->left)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            rightRotate(parent);

            parent->factor = 0;
            parent->right->factor = 0;

            break;
        } else if (parent->factor < 0 && child->factor < 0) {
            if (!(parent->right)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            leftRotate(parent);

            parent->factor = 0;
            parent->left->factor = 0;

            break;
        } else if (parent->factor > 0 && child->factor < 0) {
            if (!(child->right)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            leftRotate(child);

            if (!(parent->left)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            rightRotate(parent);

            parent->factor = 0;
            parent->right->factor = 0;

            break;
        } else if (parent->factor < 0 && child->factor > 0) {
            if (!(child->left)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            rightRotate(child);

            if (!(parent->right)) {
                std::cout << "current depth: " << depth << ", node value: " << root->value << std::endl;
            }
            leftRotate(parent);

            parent->factor = 0;
            parent->left->factor = 0;

            break;
        } else if (parent->factor == 0 && abs(child->factor) > 0) {
            parent->factor = parent->left == child ? 1 : -1;
        }

        child = parent;
        parent = parent->parent;
    }
}

void BBTree::rightRotate(Node *root) {
    assert(root && root->left);

    auto tmp = root->right;
    auto tmpValue = root->value;

    root->right = root->left;
    root->right->left = root->left->right;
    root->left = root->left->left;
    if (root->left) root->left->parent = root;
    if (tmp) tmp->parent = root->right;
    root->right->right = tmp;

    root->value = root->right->value;
    root->right->value = tmpValue;
}

void BBTree::leftRotate(Node *root) {
    assert(root && root->right);

    auto tmp = root->left;
    auto tmpValue = root->value;

    root->left = root->right;
    root->right = root->right->right;
    if (root->right) root->right->parent = root;
    root->left->right = root->left->left;
    if (tmp) tmp->parent = root->left;
    root->left->left = tmp;

    root->value = root->left->value;
    root->left->value = tmpValue;
}

Node *BBTree::find(Node *parent, const int &value) {
    Node *found = nullptr;

    if (parent) {
        if (parent->value == value) {
            found = parent;
        } else if (parent->value > value) {
            found = find(parent->left, value);
        } else {
            found = find(parent->right, value);
        }
    }

    return found;
}

bool BBTree::insert(const int &value) {
    if (!root) {
        root = new Node(value, Node::NODE_TYPE_ROOT);
        depth += 1;
    }

    Node *exist = find(value);
    bool inserted = false;
    if (!exist) {
        inserted = true;
        insert(root, value);
    }

    return inserted;
}

Node *BBTree::find(const int &value) {
    return find(root, value);
}

bool BBTree::delNode(const int &value) {
    bool deleted = false;

    Node *node = find(value);

    while (node && !(node->isLeaf())) {
        if (node->right) {
            leftRotate(node);
            assert(node->left->value == value);
            node = node->left;
        } else {
            rightRotate(node);
            assert(node->right->value == value);
            node = node->right;
        }
    }

    if (node) {
        if (node == node->parent->left) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }

        delete node;
        deleted = true;
    }

    return deleted;
}

void BBTree::printL2R() {
    printL2R(root);
}

void BBTree::printMinddle() {
    printMinddle(root);
}

void BBTree::printR2L() {
    printR2L(root);
}

void BBTree::printL2R(Node *root) {
    if (root->left) {
        printL2R(root->left);
    }
    root->print();
    if (root->right) {
        printL2R(root->right);
    }
}

void BBTree::printMinddle(Node *root) {
    root->print();
    if (root->left) {
        printMinddle(root->left);
    }
    if (root->right) {
        printMinddle(root->right);
    }
}

void BBTree::printR2L(Node *root) {
    if (root->right) {
        printR2L(root->right);
    }
    root->print();
    if (root->left) {
        printR2L(root->left);
    }
}

void BBTree::printTree(Node * node, std::map<int, std::queue<int>> *data, int level) {
    auto tmp = data->find(level); //.push(node->value);

    if (node) {
        tmp->second.push(node->value);

        printTree(node->left, data, level+1);
        printTree(node->right, data, level+1);
    }
    else if (level < depth) {
        tmp->second.push(-1);
    }
}

void BBTree::printTree() {
    auto *data = new std::map<int, std::queue<int>>();

    for (int i = 0; i < depth; ++i) {
        data->insert(std::pair<int, std::queue<int>>(i, std::queue<int>()));
    }

    printTree(root, data);

    for (int j = 0; j < depth; ++j) {
        auto tmp = data->find(j);
        auto q = tmp->second;
        while (!(q.empty())) {
            std::cout << q.front() << " ";
            q.pop();
        }

        std::cout << std::endl;
    }
}

int BBTree::getDepth() {
    return this->depth;
}

BBTree::~BBTree() {
    delete root;
}
