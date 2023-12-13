#include <iostream>

enum Color { RED, BLACK };

class RedBlackTree {
private:
    class Node {
    public:
        int data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixInsert(Node* x);
    void printTree(Node* root, int space) const;

public:
    RedBlackTree() : root(nullptr) {}
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void Insert(int key);
    // Time complexity: O(N) where N is the number of nodes in the tree
    void printTree() const;
    // Time complexity: O(1)
    void leftRotate();
    // Time complexity: O(1)
    void rightRotate();
};

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixInsert(Node* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } 
        else
         {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::Insert(int key) {
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    fixInsert(z);
}

void RedBlackTree::printTree(Node* root, int space) const {
    const int COUNT = 5;

    if (root == nullptr) {
        return;
    }

    space += COUNT;

    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) {
        std::cout << " ";
    }
    std::cout << root->data << "(" << (root->color == RED ? "R" : "B") << ")" << std::endl;

    printTree(root->left, space);
}

void RedBlackTree::printTree() const {
    // Time complexity: O(N) where N is the number of nodes in the tree
    printTree(root, 0);
}

void RedBlackTree::leftRotate() {
    // Time complexity: O(1)
    if (root != nullptr && root->right != nullptr) {
        leftRotate(root);
    }
}

void RedBlackTree::rightRotate() {
    // Time complexity: O(1)
    if (root != nullptr && root->left != nullptr) {
        rightRotate(root);
    }
}

int task_2 () {
    int N;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N;

    RedBlackTree rbt;

    std::cout << "Enter the values of the nodes: ";
    for (int i = 0; i < N; ++i) {
        int value;
        std::cin >> value;
        rbt.Insert(value);
    }

    std::cout << "Red-Black Tree:" << std::endl;
    rbt.printTree();

    std::cout << "Performing left rotation on the root:" << std::endl;
    rbt.leftRotate();
    rbt.printTree();

    std::cout << "Performing right rotation on the root:" << std::endl;
    rbt.rightRotate();
    rbt.printTree();

    return 0;
}
