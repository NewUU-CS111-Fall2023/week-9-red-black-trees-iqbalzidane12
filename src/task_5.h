#include <iostream>
#include <queue>
class BinaryTree {
private:
    class TreeNode {
    public:
        int data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;
    int countChildren(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int childrenCount = 0;
        if (node->left != nullptr) {
            childrenCount++;
        }
        if (node->right != nullptr) {
            childrenCount++;
        }

        return childrenCount;
    }

public:
    BinaryTree() : root(nullptr) {}
    // Time complexity: O(log N) on average (balanced tree), O(N) worst case (skewed tree)
    void insert(int value);
    // Time complexity: O(N) where N is the number of nodes in the tree
    void displayChildrenCount() const;
};

void BinaryTree::insert(int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = new TreeNode(value);
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = new TreeNode(value);
            return;
        } else {
            q.push(current->right);
        }
    }
}

void BinaryTree::displayChildrenCount() const {
    if (root == nullptr) {
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        int childrenCount = countChildren(current);
        std::cout << "Node " << current->data << ": " << childrenCount << " children" << std::endl;

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
int task_5 () {
    int N;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N;

    BinaryTree tree;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N; ++i) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    std::cout << "Number of children for every node:" << std::endl;
    tree.displayChildrenCount();

    return 0;
}
