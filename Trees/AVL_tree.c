/*AVL TREE: SELF BALANCING BINARY SEARCH TREE
FUNCTIONS:
- LEFT ROTATE
- RIGHT ROTATE
- INSERT
- DELETE
- DESTROY TREE (USING POSTORDER)
- INORDER & PREORDER
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
    int balance_factor;
}node;

node* create_node(int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->balance_factor = 0;
    return new_node;
}

int max(int a,int b)
{
    if(a > b)
        return a;
    else 
        return b;
}

int get_height(node* root)
{
    if(root==NULL)
    {
        return -1;
    }
    return 1 + max(get_height(root->left),get_height(root->right));
}

int update_balance_factor(node* root)
{
    if(root==NULL)
        return 0;
    root->balance_factor =  get_height(root->left) - get_height(root->right);
    return root->balance_factor;
}


node* left_rotate(node* x)   //left rotate subtree rooted at x
{
    //initial conditions
    node* y = x->right;
    node* T2 = y->left;  
    //Links of T1 & T3 not declared as, no change in linking during rotation

    //changes in linking during rotation
    y->left = x;
    x->right = T2;

    //update balance factor of x and y
    update_balance_factor(x);
    update_balance_factor(y);

    return y;  //return the root of the new rotated subtree
}

node* right_rotate(node* y)   //right rotate subtree rooted at y
{
    //initial conditions
    node* x = y->left;
    node* T2 = x->right;   
    //Links of T1 & T3 not declared as, no change in linking during rotation

    //changes in linking during rotation
    x->right = y;
    y->left = T2;

    //update balance factor of x and y
    update_balance_factor(x);
    update_balance_factor(y);

    return x;  //return the root of the new rotated subtree
}

node* insert(node* node,int key) //here, node is the root
{   
    //Perform Normal BST insertion
    if(node==NULL)   //exit condition (inserting node at correct place)
    {
        return create_node(key);
    }
    if(key < node->data)   //go in left subtree
    {
        node->left = insert(node->left,key);
    }
    else if(key > node->data)   //go in right subtree
    {
        node->right = insert(node->right,key);
    }
    else  //duplicate not allowed
    {
        return node;
    }

    //get balance factor of the ancestor node: node
    int bf = update_balance_factor(node);

    //here, 'node' is the first imbalanced node

    //Left Left case
    if(bf > 1 && key < node->left->data)
    {
        return right_rotate(node);
    }
    //Right Right case
    if(bf<-1 && key > node->right->data)
    {
        return left_rotate(node);
    }
    //Left Right case
    if(bf > 1 && key > node->left->data)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    //Right let case
    if(bf < -1 && key < node->right->data)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;  //return the unchanged node pointer
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

node* delete(node* root,int key)
{
    //Normal BST deletion
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
    
    // If the tree had only one node then return
    if(root==NULL)
    {
        return root;
    }

    //Update height and balance factor of root node
    int bf = update_balance_factor(root);

    //Here, 'root' is the node that has replaced the deleted node
    
    //If root becomes unbalanced
    //Left Left case
    if(bf > 1 && root->left->balance_factor>=0)
    {
        return right_rotate(root);
    }
    //Right Right case
    if(bf < -1 && root->right->balance_factor<=0)
    {
        return left_rotate(root);
    }
    //Left Right case
    if(bf > 1 && root->right->balance_factor < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    //Right Left case
    if(bf < -1 && root->balance_factor > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;  //return the unchanged root pointer
}

void InOrder(node* root)
{
    if(root==NULL)
        return;
    InOrder(root->left);
    printf("%d ",root->data);
    InOrder(root->right);
}

void PreOrder(node* root)
{
    if(root==NULL)
        return;
    printf("%d ",root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void destroyTree(node* root)   //PostOrder traversal
{
    if(root==NULL)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    printf("Deleted node: %d\n",root->data);
    free(root);
}

int main()
{
    node* root = create_node(8);
    root = insert(root,3);
    root = insert(root,10);
    root = insert(root,6);
    root = insert(root,4);
    root = insert(root,1);
    
    InOrder(root);printf("\n");

    root = delete(root,8);
    //root = delete(root,1);
    
    InOrder(root);printf("\n");

    destroyTree(root);

    return 0;
}