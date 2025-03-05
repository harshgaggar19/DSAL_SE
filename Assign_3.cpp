//============================================================================
// Name        : Assignment_3.cpp
// Author      : Harsh Gaggar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class ThreadedBinaryTree {
private:
    struct Node {
        Node *left, *right;
        int info;
        bool lthread;
        bool rthread;

        Node(int key) : left(nullptr), right(nullptr), info(key), lthread(true), rthread(true) {}
    };

    Node* root;

    // Insert a Node in Binary Threaded Tree
    Node* insert(Node* root, int ikey) {
        Node* ptr = root;
        Node* par = nullptr; // Parent of key to be inserted
        while (ptr != nullptr) {
            if (ikey == ptr->info) {
                cout << "Duplicate Key!" << endl;
                return root;
            }

            par = ptr; // Update parent pointer

            // Moving on left subtree
            if (ikey < ptr->info) {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }
            // Moving on right subtree
            else {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        // Create a new node
        Node* tmp = new Node(ikey);

        if (par == nullptr) {
            root = tmp;
            tmp->left = nullptr;
            tmp->right = nullptr;
        } else if (ikey < par->info) {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        } else {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false;
            par->right = tmp;
        }

        return root;
    }

    // Inorder Successor using rthread
    Node* inorderSuccessor(Node* ptr) {
        if (ptr->rthread == true)
            return ptr->right;
        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;
        return ptr;
    }

    // Printing the threaded tree in inorder traversal
    void inorder(Node* root) {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }

        Node* ptr = root;
        while (ptr->lthread == false)
            ptr = ptr->left;

        while (ptr != nullptr) {
            cout << ptr->info << " ";
            ptr = inorderSuccessor(ptr);
        }
    }

    // Preorder traversal
    void preorder(Node* root) {
        if (root == nullptr) return;

        cout << root->info << " ";

        if (root->lthread == false)
            preorder(root->left);
        if (root->rthread == false)
            preorder(root->right);
    }

    // Find Inorder Successor
    Node* inSucc(Node* ptr) {
        if (ptr->rthread == true)
            return ptr->right;

        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;

        return ptr;
    }

    // Find Inorder Predecessor
    Node* inPred(Node* ptr) {
        if (ptr->lthread == true)
            return ptr->left;

        ptr = ptr->left;
        while (ptr->rthread == false)
            ptr = ptr->right;

        return ptr;
    }

    // Case A: Deleting node with no children
    Node* caseA(Node* root, Node* par, Node* ptr) {
        if (par == nullptr)
            root = nullptr;
        else if (ptr == par->left) {
            par->lthread = true;
            par->left = ptr->left;
        } else {
            par->rthread = true;
            par->right = ptr->right;
        }

        delete ptr;
        return root;
    }

    // Case B: Deleting node with one child
    Node* caseB(Node* root, Node* par, Node* ptr) {
        Node* child = (ptr->lthread == false) ? ptr->left : ptr->right;

        if (par == nullptr)
            root = child;
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;

        Node* s = inSucc(ptr);
        Node* p = inPred(ptr);

        if (ptr->lthread == false)
            p->right = s;
        else if (ptr->rthread == false)
            s->left = p;

        delete ptr;
        return root;
    }

    // Case C: Deleting node with two children
    Node* caseC(Node* root, Node* par, Node* ptr) {
        Node* parsucc = ptr;
        Node* succ = ptr->right;

        while (succ->lthread == false) {
            parsucc = succ;
            succ = succ->left;
        }

        ptr->info = succ->info;

        if (succ->lthread == true && succ->rthread == true)
            root = caseA(root, parsucc, succ);
        else
            root = caseB(root, parsucc, succ);

        return root;
    }

    // Deleting a key from threaded BST
    Node* delThreadedBST(Node* root, int dkey) {
        Node* par = nullptr;
        Node* ptr = root;
        bool found = false;

        while (ptr != nullptr) {
            if (dkey == ptr->info) {
                found = true;
                break;
            }

            par = ptr;
            if (dkey < ptr->info) {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            } else {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        if (!found) {
            cout << "Key not found in tree" << endl;
            return root;
        }

        // Case when node has two children
        if (ptr->lthread == false && ptr->rthread == false)
            root = caseC(root, par, ptr);
        // Case when node has one child (left or right)
        else if (ptr->lthread == false || ptr->rthread == false)
            root = caseB(root, par, ptr);
        // Case when node has no children
        else
            root = caseA(root, par, ptr);

        return root;
    }

public:
    ThreadedBinaryTree() : root(nullptr) {}

    // Wrapper functions
    void insert(int ikey) {
        root = insert(root, ikey);
    }

    void deleteKey(int dkey) {
        root = delThreadedBST(root, dkey);
    }

    void printInorder() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }

    void printPreorder() {
        cout << "Preorder traversal: ";
        preorder(root);
        cout << endl;
    }
};

// Driver Program
int main() {
    ThreadedBinaryTree tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(16);
    tree.insert(14);
    tree.insert(17);
    tree.insert(13);

    tree.printInorder();

    // Deleting node with key 20
    tree.deleteKey(20);

    tree.printInorder();
    tree.printPreorder();

    return 0;
}
