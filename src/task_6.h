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
    int calculateBlackHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftBlackHeight = calculateBlackHeight(node->left);
        int rightBlackHeight = calculateBlackHeight(node->right);
        if (leftBlackHeight != rightBlackHeight) {
            return -1;
        }
        if (node->color == BLACK) {
            return leftBlackHeight + 1;
        } else {
            return leftBlackHeight;
        }
    }

public:
    RedBlackTree() : root(nullptr) {}
    // Time complexity: O(log N) in the average case, O(N) in the worst case (due to rotations)
    void insert(int key);
    // Time complexity: O(N^2) where N is the number of nodes in the tree (due to repeated calculations)
    void displayBlackHeight() const;
};

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
}

void RedBlackTree::displayBlackHeight() const {
    if (root == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        int blackHeight = calculateBlackHeight(current);
        if (blackHeight == -1) {
            std::cout << "Node " << current->data << ": Violation detected!" << std::endl;
        } else {
            std::cout << "Node " << current->data << ": Black Height = " << blackHeight << std::endl;
        }

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
int task_6 () {
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

    std::cout << "Black Height of every node:" << std::endl;
    rbt.displayBlackHeight();

    return 0;
}
