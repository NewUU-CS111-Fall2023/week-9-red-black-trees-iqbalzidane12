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
    void fixDelete(Node* x);
    void transplant(Node* u, Node* v);
    Node* findMin(Node* node);
    void deleteNode(Node* z);
    void insertFix(Node* x);
    void printTree(Node* root, int space) const;

public:
    RedBlackTree() : root(nullptr) {}
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void Insert(int key);
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void Delete(int key);
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
        } else {
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

void RedBlackTree::insertFix(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

RedBlackTree::Node* RedBlackTree::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void RedBlackTree::deleteNode(Node* z) {
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFix(x);
    }

    delete z;
}

void RedBlackTree::fixDelete(Node* x) {

    insertFix(x);
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

void RedBlackTree::Delete(int key) {
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    Node* z = root;
    while (z != nullptr) {
        if (key < z->data) {
            z = z->left;
        } else if (key > z->data) {
            z = z->right;
        } else {
            deleteNode(z);
            return;
        }
    }
    std::cout << "Node with key " << key << " not found in the tree." << std::endl;
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

int task_3 () {
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

    std::cout << "Enter the node value to delete: ";
    int deleteValue;
    std::cin >> deleteValue;
    rbt.Delete(deleteValue);

    std::cout << "Tree after deletion:" << std::endl;
    rbt.printTree();

    return 0;
}
