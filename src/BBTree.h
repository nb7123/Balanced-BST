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
     * rotate process
     *
     * illustration of a full binary search tree:
     *                A
     *              /   \
     *             B    C
     *            / \  / \
     *           D  E F  G
     * tree data sort: D < B < E < A < F < C < G
     *
     * left rotate this tree, expected result:
     *
     *                      A (value = C->value)
     *                    /   \
     * (value = A->value)B    G
     *                  / \
     *                 B  F
     *                / \
     *               D  E
     *
     * tree data sort: D < B < E < B(value=A->value) < F < A(value=C->value) < G
     *
     * seven step:
     * 1- let root = A, and cache root->left pointer and root->value:
     *      root = A;
     *      T = root->left;
     *      TV = root->value;
     *      now tree:
     *                A
     *              /   \
     *             B    C
     *            / \  / \
     *           D  E F  G
     *      tree T:
     *              B
     *             / \
     *            D  E
     *
     * 2- let root left child pointer point to root right child pointer:
     *      root->left = root->right;
     *      now tree:
     *                A
     *              /   \
     *             C    C
     *            / \  / \
     *           F  G F  G
     *
     * 3- let root right child pointer point to root right child right child pointer:
     *      root->right = root->right->right;
     *      now tree:
     *                A
     *              /   \
     *             C    G
     *            / \
     *           F  G
     *
     * 4- let root left child right child pointer point to root right child left child pointer:
     *      root->left->right = root->left->left;
     *      now tree:
     *                A
     *              /   \
     *             C    G
     *            / \
     *           F  F
     *
     * 5- let root left child left child pointer point to original tree root left child(T):
     *      root->left->left = T;
     *      now tree:
     *                A
     *              /   \
     *             C    G
     *            / \
     *           B  F
     *          / \
     *         D  E
     * 6- change root and root left child node value:
     *      root->value = root->left->value;
     *      root->left-value = TV;
     *      now tree:
     *                      A (value = C->value)
     *                    /   \
     * (value = A->value)B    G
     *                  / \
     *                 B  F
     *                / \
     *               D  E
     * now tree sort:
     * D < B < E < B(value = A->value) < F < A(value = C->value) < G
     * but the real value sort is:
     * D < B < E < A < F < C < G
     *
     *
     * we are success
     * have fun, body  ^_^
     *
     * @param root
     */
    void leftRotate(Node *root);

    /**
 * rotate process
 *
 * illustration of a full binary search tree:
 *                A
 *              /   \
 *             B    C
 *            / \  / \
 *           D  E F  G
 * tree data sort: D < B < E < A < F < C < G
 *
 * right rotate this tree, expected result:
 *                A (value = B->value)
 *              /  \
 *             D   C (value = A->value)
 *                / \
 *               E  C
 *                 / \
 *                F  G
 * tree data sort: D < A(value is B) < E < C(value is A) < F < C < G
 *
 * seven step:
 * 1- let root = A, cache root->right pointer and root->value:
 *      root = A;
 *      T = root->right;
 *      TV = root->value;
 *      now tree:
 *                A
 *              /   \
 *             B    C
 *            / \  / \
 *           D  E F  G
 *      tree T:
 *              C
 *             / \
 *            F  G
 *
 * 2- let root right child pointer point  to root right child pointer:
 *      root->right = root->left;
 *      now tree:
 *                A
 *              /   \
 *             B    B
 *            / \  / \
 *           D  E D  E
 *
 * 3- let root left child pointer point to root left child left child pointer:
 *      root->left = root->left->left;
 *      now tree:
 *                A
 *              /   \
 *             D    B
 *                 / \
 *                D  E
 *
 * 4- let root right child left pointer point to root left child right pointer:
 *      root->right->left = root->right->right;
 *      now tree:
 *                A
 *              /   \
 *             D    B
 *                 / \
 *                E  E
 *
 * 5- let root right child right child pointer point to original tree root right child pointer(T):
 *      root->right->right = T;
 *      now tree:
 *                A
 *              /   \
 *             D    B
 *                 / \
 *                E  C
 *                  / \
 *                 F  G
 * 6- change root and root right child node value:
 *      root->value = root->right->value;
 *      root->right-value = TV;
 *      now tree:
 *                A (value = B)
 *              /   \
 *             D    B (value = A)
 *                 / \
 *                E  C
 *                  / \
 *                 F  G
 * now tree sort:
 * D < A < E < B < F < C < G
 * but the real value sort is:
 * D < B < E < A < F < C < G
 *
 *
 * we are success
 * have fun, body  ^_^
 *
 * @param root
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
