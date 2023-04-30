/************
AVL TREES: SELF BALANCING TREES
OPERATIONS:
- INSERTION
- DELETION

AUXILLARY FUNCTIONS:
- GET HEIGHT & GET BALANCE FACTOR
- LEFT ROTATE & RIGHT ROTATE
- InOrder & PreOrder traversals
************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
    int height;
}node;

node* create_node(int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

int get_height(node* n)
{
    if(n==NULL)
        return 0;
    return n->height;
}

int get_balance_factor(node* n)
{
    if(n==NULL)
        return 0;
    return get_height(n->left) - get_height(n->right);
}

int max(int a,int b)
{
    if(a > b)
        return a;
    else 
        return b;
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

    //update height of x and y
    x->height = max(get_height(x->right), get_height(x->left)) + 1;
    y->height = max(get_height(y->right), get_height(y->left)) + 1;
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

    //update height of x and y
    x->height = max(get_height(x->right), get_height(x->left)) + 1;
    y->height = max(get_height(y->right), get_height(y->left)) + 1;
    return x;  //return the root of the new rotated subtree
}

node* insert(node* node, int key)   //here, node is the root
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

    //update height and get balance factor of the ancestor node: node
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    int bf = get_balance_factor(node);

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
    root->height = max(get_height(root->left), get_height(root->right))+1;
    int bf = get_balance_factor(root);

    //Here, 'root' is the node that has replaced the deleted node
    
    //If root becomes unbalanced
    //Left Left case
    if(bf > 1 && get_balance_factor(root->left)>=0)
    {
        return right_rotate(root);
    }
    //Right Right case
    if(bf < -1 && get_balance_factor(root->right)<=0)
    {
        return left_rotate(root);
    }
    //Left Right case
    if(bf > 1 && get_balance_factor(root->right) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    //Right Left case
    if(bf < -1 && get_balance_factor(root) > 0)
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

int main()
{
    node* root = NULL;
    root = insert(root,8);
    root = insert(root,3);
    root = insert(root,10);
    root = insert(root,1);
    root = insert(root,6);
    root = insert(root,4);
    root = insert(root,5);
    root = insert(root,2);
    root = insert(root,9);
    root = insert(root,12);
    root = insert(root,7);
    PreOrder(root);
    printf("\n");
    delete(root,6);
    //InOrder(root);
    PreOrder(root);
    printf("\n");
    printf("Element found:%d ",Search(root,10));
    return 0;
}
