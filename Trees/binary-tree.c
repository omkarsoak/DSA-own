/************
BINARY TREE
OPERATIONS:
- CreateNode
- InOrder, PreOrder, PostOrder traversals
- isLeaf
************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
}node;

typedef node* tree;

node* create_node(int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void PreOrder(node* root)
{
    if(root == NULL)   //exit condition
		return;
    printf("%d ",root->data);  //root
    PreOrder(root->left);      //left subtree
    PreOrder(root->right);     //right subtree
}

void PostOrder(node* root)
{
    if(root==NULL)   //exit condition
        return;
    PostOrder(root->left);     //left subtree
    PostOrder(root->right);    //right subtree
    printf("%d ",root->data);  //root
}

void InOrder(node* root)
{
    if(root==NULL)  //exit condition
        return;
    InOrder(root->left);       //left subtree
    printf("%d ",root->data);  //root
    InOrder(root->right);      //right subtree
}

int is_leaf(node* root)
{
    if(root->left==NULL && root->right==NULL)
        return 1;
    else 
        return 0;
}

int main()
{
    node* root;
    root = create_node(1);
    root->left = create_node(2);
    root->right= create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->right = create_node(7);
    root->right->left = create_node(8);
    root->right->right->right = create_node(9);
    //PreOrder(root);
    //PostOrder(root);
    InOrder(root);
    return 0;
}