#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

// Structure of a tree node
struct Node {
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree violations after insertion
void fixViolation(struct Node** root, struct Node* newNode) {
    struct Node* parent = NULL;
    struct Node* grandParent = NULL;

    while ((newNode != (*root)) && (newNode->color != BLACK) && (newNode->parent->color == RED)) {
        parent = newNode->parent;
        grandParent = newNode->parent->parent;

        if (parent == grandParent->left) {
            struct Node* uncle = grandParent->right;

            // Case 1: Uncle is also red
            if (uncle != NULL && uncle->color == RED) {  
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandParent;
            } else {
                // Case 2: New node is the right child of its parent
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 3: New node is the left child of its parent
                rightRotate(root, grandParent);
                parent->color = BLACK;
                grandParent->color = RED;
                newNode = parent;
            }
        } else {
            struct Node* uncle = grandParent->left;

            // Case 1: Uncle is also red
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandParent;
            } else {
                // Case 2: New node is the left child of its parent
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 3: New node is the right child of its parent
                leftRotate(root, grandParent);
                parent->color = BLACK;
                grandParent->color = RED;
                newNode = parent;
            }
        }
    }

    (*root)->color = BLACK;
}

// Function to insert a node in the Red-Black Tree
struct Node* insertNode(struct Node* root, struct Node* newNode) {
    if (root == NULL)
        return newNode;

    struct Node* current = root;
    struct Node* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixViolation(&root, newNode);
    return root;
}

// Function to perform inorder traversal of the Red-Black Tree
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct Node* root = NULL;
    root = insertNode(root, createNode(7));
    root = insertNode(root, createNode(3));
    root = insertNode(root, createNode(18));
    root = insertNode(root, createNode(10));
    root = insertNode(root, createNode(22));
    root = insertNode(root, createNode(8));
    root = insertNode(root, createNode(11));
    root = insertNode(root, createNode(26));
    root = insertNode(root, createNode(2));
    root = insertNode(root, createNode(6));
    root = insertNode(root, createNode(13));

    printf("Inorder Traversal of the Red-Black Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
