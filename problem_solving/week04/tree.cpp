#include <iostream>

class TreeNode {
public:
    int val;
    TreeNode* children[2];

    TreeNode(int val) {
        this->val = val;
        this->children[0] = nullptr;
        this->children[1] = nullptr;
    }

    ~TreeNode() {
        delete children[0];
        delete children[1];
    }

    void insert(int val) {
        TreeNode** current = &children[val > this->val];
        if (*current == nullptr) {
            *current = new TreeNode(val);
        }
        else {
            (*current)->insert(val);
        }
    }

    void traverseInOrder() {
        if (children[0] != nullptr) {
            children[0]->traverseInOrder();
        }
        std::cout << val << " ";
        if (children[1] != nullptr) {
            children[1]->traverseInOrder();
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->insert(5);
    root->insert(15);
    root->insert(8);
    root->insert(12);
    root->traverseInOrder();
    delete root;
    return 0;
}
