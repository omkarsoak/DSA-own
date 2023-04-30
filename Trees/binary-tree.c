/************
BINARY TREE
OPERATIONS:
- CreateNode
- Insert (using toss)
- Search
- InOrder, PreOrder, PostOrder traversals
- isLeaf
************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int Search(node* root,int key)   //returns 1 if found
{
    if(root==NULL)   //exit condition(key not found)
    {
        return 0;
    }
    if(key == root->data)   //exit condition (key found)
    {
        return 1;
    }

    int left_result = Search(root->left,key);
    if(left_result==1)
    {
        return 1;
    }

    int right_result = Search(root->right,key);
    if(right_result==1)
    {
        return 1;
    }
}

//generates 0 or 1 randomly at every function call with equal probability 
int toss()
{
    //srand should be called only once
    static int num = 0;
    if (num!=1) 
    {
        srand(time(NULL));
        num = 1;
    }
    return rand() % 2;
}

void Insert(node** root_ref,int key)
{
    node* root = (*root_ref);
    node* prev = NULL;
    if(root==NULL)   //base case
    {
        root = create_node(key);
        return;
    }
   
    while(1)  //infinite loop as return statement is included
    {
        prev = root;
        if(root->data == key)   //check if duplicate (no insertion)
        {
            return;
        }
        else if(toss() == 0)   //go in left subtree
        {
            if(prev->left==NULL)   //leaf node found
            {
                prev->left = create_node(key);
                return;
            }
            else
            {
                root = root->left;
            }
        }
        else if(toss() == 1)   //go in right subtree
        {
            if(prev->right==NULL)  //leaf node found
            {
                prev->right = create_node(key);
                return;
            }
            else
            {
                root = root->right;
            }
        }
    }
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
    node* root = NULL;
    root = create_node(1);
    Insert(&root,10);
    Insert(&root,6);
    Insert(&root,8);
    Insert(&root,4);
    Insert(&root,3);
    InOrder(root);
    printf("\nfound %d\n",Search(root,8));
    printf("found %d\n",Search(root,6));
    printf("found %d\n",Search(root,11));

    return 0;
}
