//
// Created by michael on 18-9-11.
//

#ifndef BTREE_NODE_H
#define BTREE_NODE_H


class Node {
public:
    static int NODE_TYPE_LEFT;
    static int NODE_TYPE_RIGHT;
    static int NODE_TYPE_ROOT;
    static int NODE_TYPE_UNKNOWN;

    explicit Node(int value, int type = NODE_TYPE_UNKNOWN);

    Node *parent;
    Node *left;
    Node *right;
    int value;
    int nodeType;
    /**
     * 平衡因子 = left height- right height
     * -1: left sub tree height higher than right sub tree
     * 0: left sub tree height equal to right sub tree
     * 1: left sub tree height smaller than right sub tree
     */
    int factor;

    void print();
    bool isLeaf();

    ~Node();
};


#endif //BTREE_NODE_H
