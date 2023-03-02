/***************
BINARY SEARCH TREES (BST):
OPERATIONS:
- SEARCHING (iterative & recursive)
- INSERTION (iterative & recursive)
- DELETION
- isBST (check if a tree is BST)
- InOrder traversal
*****************/
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

void InOrder(node* root)
{
    if(root==NULL)
        return;
    InOrder(root->left);
    printf("%d ",root->data);
    InOrder(root->right);
}

//Recursive search (returns ptr to node of key)
node* search(node* root,int key)
{
    if(root == NULL || root->data == key)  //exit condition (key found or not found)
        return root;   

    else if(key < root->data)    //key is less than root (so search in left subtree)
        return search(root->left,key);

    else if(key > root->data)   //key is greater than root (so search in right subtree)
        return search(root->right,key);
    
}

//Recursive search (returns 1 if found)
int Search(node* root,int key)
{
    if(root == NULL)  //exit condition (key not found)
        return 0;   
    else if(root->data == key)  //exit condition (key found)
        return 1;
    else if(key < root->data)    //key is less than root (so search in left subtree)
        return Search(root->left,key);

    else if(key > root->data)   //key is greater than root (so search in right subtree)
        return Search(root->right,key);
        
}

//iterative search
int iterative_search(node* root,int key)
{
    while(root!=NULL)
    {
        if(root->data == key)
            return 1;

        else if(key < root->data)   //search in left subtree
            root = root->left;
    
        else if(key > root->data)   //search in right subtree
            root = root->right;
    }
    return 0;    //if root becomes NULL (key not found)
}

//similarly we can write iterative approach for returning a ptr to node of key

//iterative insertion
void insert(node** root_ref,int key)
{
    node* root = (*root_ref);
    node* prev = NULL;
    //traversing to right leaf node
    while(root!=NULL)   //until you reach a leaf node
    {
        prev = root;
        if(root->data == key)   //check if duplicate (no insertion)
        {
            return;
        }
        else if(key < root->data)   //go in left subtree
        {
            root = root->left;
        }
        else if(key > root->data)   //go in right subtree
        {
            root = root->right;
        }
    }
    //insertion at leaf node (prev)
    node* new_node = create_node(key);
    if(key < prev->data)
    {
        prev->left = new_node;
    }
    else if(key > prev->data)
    {
        prev->right = new_node;
    }
}

//Recursive insertion
node* Insert(node* root,int key)
{
    if(root==NULL)   //exit condition (inserting node at correct place)
    {
        return create_node(key);
    }
    if(key < root->data)   //go in left subtree
    {
        root->left = Insert(root->left,key);
    }
    else if(key > root->data)   //go in right subtree
    {
        root->right = Insert(root->right,key);
    }
    return root;   //incase of duplicate (no insertion)
}

node* InOrderPredecessor(node* root)   //rightmost element in left subtree
{
    root = root->left;
    //traverse to find rightmost element
    while(root->right!=NULL)
    {
        root = root->right;
    }
    return root;
}

node* InOrderSuccessor(node* root)   //leftmost element in right subtree
{
    root = root->right;
    //traverse to find leftmost element
    while(root->left!=NULL)
    {
        root = root->left;
    }
    return root;
}

node* Delete(node* root,int key)   //using inorder predecessor method
{
    if(root==NULL)   //base case (empty tree)
    {
        return NULL;
    }

    //searching the node to be deleted
    if(key < root->data)
    {
        root->left = Delete(root->left,key);
    }
    else if(key > root->data)
    {
        root->right = Delete(root->right,key);
    }

    else  //key to be deleted is found
    {
        //Case 1 & 2: node with no child(leaf node) or with only 1 child
        if(root->left==NULL)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
        
        //Case 3: node with 2 children
        node* temp = InOrderPredecessor(root);  //get the inorder predecessor
        root->data = temp->data;   //copy its data into the deleted nodes position
        root->left = Delete(root->left,temp->data);     //delete the inorder predecessor
    }
    return root;
}

node* delete(node* root,int key)   //using InOrder successor method
{
    if(root==NULL)   //base case (empty tree)
    {
        return NULL;
    }

    //searching the node to be deleted
    if(key < root->data)
    {
        root->left = delete(root->left,key);
    }
    else if(key > root->data)
    {
        root->right = delete(root->right,key);
    }

    else  //key to be deleted is found
    {
        //Case 1 & 2: node with no child(leaf node) or with only 1 child
        if(root->left==NULL)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
        
        //Case 3: node with 2 children
        node* temp = InOrderSuccessor(root);  //get the inorder successor
        root->data = temp->data;   //copy its data into the deleted nodes position
        root->right = delete(root->right,temp->data);     //delete the inorder successor
    }
    return root;
}

int isBST(node* root)   //based on InOrder traversal
{
    static node* prev = NULL;   //it is static as, it should not be NULL at every function call
    if(root!=NULL)
    {
        if(isBST(root->left)!=1)    //checking left subtree
        {
            return 0;
        }
        
        //checking if property of BST is maintained
        if(prev!=NULL && root->data <= prev->data)
        {
            return 0;
        }
        prev = root;   
        //NOTE: prev is the previous node in the inorder traversal & not the previous node in the tree

        return isBST(root->right);   //checking right subtree
    }
    else   //root == NULL (i.e it is leaf node or it is an empty tree)
    {
        return 1;
    }
}

int main()
{
    node* root = NULL;
    root = create_node(8);
    Insert(root,3);
    Insert(root,10); 
    Insert(root,1); 
    Insert(root,6); 
    Insert(root,4);
    InOrder(root);
    //Delete(root,3);
    delete(root,3);
    InOrder(root);
    printf("\n%d ",isBST(root));
    return 0;
}