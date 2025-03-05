//============================================================================
// Name        : Assignment_2.cpp
// Author      : Harsh Gaggar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
using namespace std;

// Structure for a node in the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST{
public:
	Node* insert(Node* root, int value);
	int longestPath(Node* root);
	int findMin(Node* root) ;
	int findMax(Node* root);
	void swapChildren(Node* root);
	bool search(Node* root, int value);
	void inorderTraversal(Node* root);
};

Node* BST:: insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to find the number of nodes in the longest path (Height of the tree)
int BST:: longestPath(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = longestPath(root->left);
    int rightHeight = longestPath(root->right);

    return max(leftHeight, rightHeight) + 1;
}

int BST::findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

int BST:: findMax(Node* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->data;
}

void BST:: swapChildren(Node* root) {
    if (root == nullptr) {
        return;
    }

    swap(root->left, root->right);

    swapChildren(root->left);
    swapChildren(root->right);
}

bool BST:: search(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == value) {
        return true;
    }

    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void BST::inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

int main() {
	BST b1;
    Node* root = nullptr;

    // Step 1: Insert nodes into the tree (example sequence)
    root = b1.insert(root, 50);
    root = b1.insert(root, 30);
    root = b1.insert(root, 20);
    root = b1.insert(root, 40);
    root = b1.insert(root, 70);
    root = b1.insert(root, 60);
    root = b1.insert(root, 80);
    root = b1.insert(root, 25);

    // Print the tree in inorder (sorted order)
    cout << "Inorder traversal of BST before insertion: ";
    b1.inorderTraversal(root);
    cout << endl;

    // Step 2: Insert a new node (e.g., 10)
    root = b1.insert(root, 10);
    root = b1.insert(root, 15);
    cout << "Inorder traversal after inserting 10: ";
    b1.inorderTraversal(root);
    cout << endl;

    // Step 3: Find the number of nodes in the longest path
    int longestPathLength = b1.longestPath(root);
    cout << "Number of nodes in the longest path: " << longestPathLength << endl;

    // Step 4: Find the minimum and maximum values in the tree
    int minValue = b1.findMin(root);
    int maxValue = b1.findMax(root);
    cout << "Minimum value in the tree: " << minValue << endl;
    cout << "Maximum value in the tree: " << maxValue << endl;

    // Step 5: Swap the left and right children at every node
    b1.swapChildren(root);
    cout << "Inorder traversal after swapping left and right children: ";
    b1.inorderTraversal(root);
    cout << endl;

    // Step 6: Search for an element (e.g., 40)
    int searchValue = 40;
    if (b1.search(root, searchValue)) {
        cout << "Element " << searchValue << " found in the tree." << endl;
    } else {
        cout << "Element " << searchValue << " not found in the tree." << endl;
    }

    return 0;
}
