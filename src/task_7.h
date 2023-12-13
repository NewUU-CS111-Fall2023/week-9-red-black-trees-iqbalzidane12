#include <iostream>
#include <queue>
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
    void rightRotate(Node* y);
    void fixInsert(Node* z);
    Node* searchNode(int key) const;
    int getHeight(Node* node) const;

public:
    RedBlackTree() : root(nullptr) {}
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void insert(int key);
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void search(int key) const;
    // Time complexity: O(N) where N is the number of nodes in the tree
    void display() const;
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

void RedBlackTree::fixInsert(Node* z){
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

void RedBlackTree::insert(int key) {
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

Node* RedBlackTree::searchNode(int key) const {
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    Node* current = root;
    while (current != nullptr && current->data != key) {
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

int RedBlackTree::getHeight(Node* node) const {
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

void RedBlackTree::search(int key) const {
    Node* result = searchNode(key);
    if (result != nullptr) {
        int height = getHeight(result);
        std::cout << key << " is found, its height is " << height << std::endl;
    } else {
        std::cout << key << " is not found" << std::endl;
    }
}

void RedBlackTree::display() const {
    // Time complexity: O(N) where N is the number of nodes in the tree
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        std::cout << current->data << "(" << (current->color == RED ? "R" : "B") << ") ";

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    std::cout << std::endl;
}

int task_7 () {
    int N;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N;

    RedBlackTree rbt;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N; ++i) {
        int value;
        std::cin >> value;
        rbt.insert(value);
    }

    std::cout << "Enter the search value: ";
    int searchValue;
    std::cin >> searchValue;

    rbt.search(searchValue);

    return 0;
}
