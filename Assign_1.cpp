//============================================================================
// Name        : Assignment_1.cpp
// Author      : Harsh Gaggar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class BTnode {
public:
    char data;
    BTnode *left;
    BTnode *right;
    BTnode(char key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

class BT {
private:
    BTnode* root;

public:
    BT() : root(nullptr) {}

    BTnode* createBT();
    void preorder(BTnode *node);
    void inorder(BTnode *node);
    void postorder(BTnode *node);
    int height(BTnode *node);
    int cntLeaf(BTnode *node);
    int cntNonLeaf(BTnode *node);
    BTnode* copyTree(BTnode *root);
    void eraseTree(BTnode *&node);

    BT& operator=(const BT& other) {
        if (this == &other) return *this;
        eraseTree(root);
        root = copyTree(other.root);
        return *this;
    }

    void eraseTree() {
        eraseTree(root);
        root = nullptr;
    }

    BTnode* getRoot() { return root; }

    ~BT() {
        eraseTree(root);
    }
};

// Creating a sample binary tree
BTnode* BT::createBT() {
    root = new BTnode('a');
    root->left = new BTnode('b');
    root->right = new BTnode('c');
    root->left->left = new BTnode('d');
    root->left->right = new BTnode('e');
    root->right->left = new BTnode('f');

    return root;
}

// Preorder traversal
void BT::preorder(BTnode *node) {
    if (node == nullptr) return;

    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

// Inorder traversal
void BT::inorder(BTnode *node) {
    if (node == nullptr) return;

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

// Postorder traversal
void BT::postorder(BTnode *node) {
    if (node == nullptr) return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

// Corrected height function (recursive)
int BT::height(BTnode *node) {
    if (node == nullptr) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// Counting leaf nodes
int BT::cntLeaf(BTnode* node) {
    if (node == nullptr) {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    return cntLeaf(node->left) + cntLeaf(node->right);
}

// Counting internal nodes
int BT::cntNonLeaf(BTnode* node) {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr))
        return 0;

    return 1 + cntNonLeaf(node->left) + cntNonLeaf(node->right);
}

// Copying tree recursively
BTnode* BT::copyTree(BTnode* root) {
    if (!root) return nullptr;
    BTnode* newNode = new BTnode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Erasing tree recursively
void BT::eraseTree(BTnode* &node) {
    if (!node) return;
    eraseTree(node->left);
    eraseTree(node->right);
    delete node;
    node = nullptr;
}

int main() {
    BT b1;
    b1.createBT();
    BTnode *root = b1.getRoot();

    cout << "Preorder: ";
    b1.preorder(root);
    cout << endl;

    cout << "Inorder: ";
    b1.inorder(root);
    cout << endl;

    cout << "Postorder: ";
    b1.postorder(root);
    cout << endl;

    cout << "Height of tree: " << b1.height(root) << endl;

    cout << "Number of leaf nodes: " << b1.cntLeaf(root) << endl;

    cout << "Number of internal nodes: " << b1.cntNonLeaf(root) << endl;

    // Copy tree using overloaded assignment operator
    BT copiedTree;
    copiedTree = b1;
    cout << "Copied tree inorder traversal: ";
    copiedTree.inorder(copiedTree.getRoot());
    cout << endl;

    // Erasing the copied tree
    copiedTree.eraseTree();
    cout << "Tree erased." << endl;

    return 0;
}
