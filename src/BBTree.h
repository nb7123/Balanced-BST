//
// Created by michael on 18-9-11.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include <stack>
#include <queue>
#include <map>

#include "Node.h"

class BBTree {
private:
    Node *root;
    int depth;

    void balanceTree(Node *root);

    void insert(Node *parent, const int &value);
    /**
     * insert child node as root tree left node (root -> left = node)
     * @param root
     * @param node
     */
    void insertNode(Node *root, Node *node);

    /**
     * insert child node as root tree right node right node child(root -> right -> right = node)
     * @param root
     * @param node
     */
    void leftRotate(Node *root);

    /**
     * insert child node as root tree left node right node child(root -> left -> right = node)
     * @param root
     * @param node
     */
    void rightRotate(Node *root);

    Node *find(Node *parent, const int &value);

    void printL2R(Node *root);
    void printMinddle(Node *root);
    void printR2L(Node *root);
    void printTree(Node *node, std::map<int, std::queue<int>> *data, const int level = 0);

public:
    BBTree();

    bool insert(const int &value);
    Node *find(const int &value);
    bool delNode(const int &value);
    void printL2R();
    void printMinddle();
    void printR2L();
    void printTree();
    int getDepth();

    ~BBTree();
};


#endif //BTREE_BTREE_H
