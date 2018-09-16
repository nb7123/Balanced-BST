# Balanced-BST
Balanced binary search tree cpp implementation
```
 left rotate process

 illustration of a full binary search tree:
                A
              /   \
             B     C
            / \   / \
           D   E F   G
 tree data sort: D < B < E < A < F < C < G

 left rotate this tree, expected result:

                      A (value = C->value)
                    /   \
 (value = A->value)B    G
                  / \
                 B   F
                / \
               D   E

 tree data sort: D < B < E < B(value=A->value) < F < A(value=C->value) < G

 seven step:
 1- let root = A, and cache root->left pointer and root->value:
      root = A;
      T = root->left;
      TV = root->value;
      now tree:
                A
              /   \
             B     C
            / \   / \
           D   E F   G
      tree T:
              B
             / \
            D   E

 2- let root left child pointer point to root right child pointer:
      root->left = root->right;
      now tree:
                A
              /   \
             C     C
            / \   / \
           F   G F   G

 3- let root right child pointer point to root right child right child pointer:
      root->right = root->right->right;
      now tree:
                A
              /   \
             C     G
            / \
           F   G

 4- let root left child right child pointer point to root right child left child pointer:
      root->left->right = root->left->left;
      now tree:
                A
              /   \
             C     G
            / \
           F   F

 5- let root left child left child pointer point to original tree root left child(T):
      root->left->left = T;
      now tree:
                A
              /   \
             C     G
            / \
           B   F
          / \
         D   E
 6- change root and root left child node value:
      root->value = root->left->value;
      root->left-value = TV;
      now tree:
                      A (value = C->value)
                    /   \
 (value = A->value)B     G
                  / \
                 B   F
                / \
               D   E
  now tree sort:
  D < B < E < B(value = A->value) < F < A(value = C->value) < G
  but the real value sort is:
  D < B < E < A < F < C < G
 
 
  we are success
  have fun  ^_^
```
