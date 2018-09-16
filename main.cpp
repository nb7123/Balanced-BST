#include <iostream>
#include "src/BBTree.h"

int main() {
    std::cout << "BTee test..." << std::endl;
    std::cout << "Generate 100 integers..." << std::endl;

    int count = 2000;

    int *values = static_cast<int *>(malloc(count * sizeof(int)));

    srand(time(nullptr));

    for (int i = 0; i < count; ++i) {
        values[i] = static_cast<int>(random());
    }

    std::cout << "Build BTree use the " << count << " integer values..." << std::endl;

    BBTree bTree = BBTree();

    for (int i = 0; i < count; ++i) {
        bTree.insert(values[i]);
    }

    std::cout << "Print BTree..." << std::endl;
//    std::cout << "Print BTree left to right" << std::endl;
//    bTree.printL2R();
//
//    std::cout << "Print BTree right to left" << std::endl;
//    bTree.printR2L();
//
//    std::cout << "Print BTree middle" << std::endl;
//    bTree.printMinddle();
//
//    std::cout << "Print BTree" << std::endl;
    bTree.printTree();

    auto value = values[random()%count];
    auto found = bTree.find(value);

    std::cout << "Find value: " << value
              << " node info, left child->" << found->left
              << ", right child->" << found->right
              << ", node value:" << found->value << std::endl;


    std::cout << "Delete value: " << value << std::endl;

    auto deleted = bTree.delNode(value);
    std::cout << "Delete result: " << deleted << std::endl;

    found = bTree.find(value);
    std::cout << "Find value: " << value
              << ", node info: " << found << std::endl;

    std::cout << "BTree height: " << bTree.getDepth() << std::endl;

    return 0;
}