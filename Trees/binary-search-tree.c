/***************
BINARY SEARCH TREES (BST):
OPERATIONS:
- SEARCHING (iterative & recursive)
- INSERTION (iterative & recursive)
- DELETION  (iterative & recrusive- inorder successor & predecessor)
- isBST(check if a tree is BST)
- InOrder traversal

METHODS:
- count total nodes (recursive & iterative - using stack & queue)
- count leaf nodes (recursive & iterative - using queue)
- count internal nodes (recursive & iterative - using queue)
- isFulltree
- iterative Inorder, Preorder, Postorder (using stack)
- Level order traversal (using queue)
- height of tree
- find root to node path
- find ancestors of a given node
- mirror a tree
- check if tree is mirror

*****************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
}node;

typedef node* BST;

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

//iterative insertion
void insert(node* root1,int key)
{
    node* root = root1;
    node* prev = NULL;
    //traversing to correct leaf node
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
    if(key < prev->data)
    {
        prev->left = create_node(key);
    }
    else if(key > prev->data)
    {
        prev->right = create_node(key);
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

void iterative_delete(node* root,int key)   //using Inorder successor method
{
    node* prev = NULL;
    node* curr = root;

    while(curr!=NULL && curr->data!=key)
    {
        //searching the node to be deleted
        prev = curr;
        if(key < curr->data)
        {
            curr = curr->left;
        }
        else if(key > curr->data)
        {
            curr = curr->right;
        }
    }
    
    if(curr==NULL)   //key not found
    {
        return;
    }
    //key to be deleted is found at curr

    //Case 1:leaf node
    if(curr->left==NULL && curr->right == NULL)
    {
        if(prev->left == curr) 
            prev->left = NULL;
        else
            prev->right = NULL;
        free(curr);
        return;
    }

    //Case 2: node with only 1 child
    if(curr->left==NULL && curr->right!=NULL)  //right child only
    {
        if(prev->right == curr)
            prev->right = curr->right;
        else
            prev->left = curr->right;
        free(curr);
        return;
    }
    else if(curr->right==NULL && curr->left!=NULL)  //left child only
    {
        if(prev->right == curr)
            prev->right = curr->left;
        else
            prev->left = curr->left;
        free(curr);
        return;
    }
    
    //Case 3: node with 2 children

    //finding inorder successor
    node* temp = curr->right;
    node* temp_prev = NULL;
    while(temp->left!=NULL)
    {
        temp_prev = temp;
        temp = temp->left;
    }

    if(temp_prev!=NULL)  
    {
        temp_prev->left = temp->right;
    }
    else         //inorder successor = curr->right (while loop did not run)
    {
        curr->right = temp->right;
    }
    curr->data = temp->data;   //copy its data into the deleted nodes position
    free(temp);
    return;
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
        
        //checking if property of node* is maintained
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

/*STACK DEFINITION AND FUNCTIONS*/

//array representation of stack of nodes
typedef struct Stack
{
    int size;
    int top;
    node** arr;  //arr of pointers pointing to nodes
}Stack;

//stack operations for node stack
void Stack_initialize(Stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->arr = (node**)malloc(s->size*sizeof(node*));
}

int isEmpty(Stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int isFull(Stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;} 
}

void Push(Stack *ptr,node* root)
{
    if(isFull(ptr)==1)  //stack overflow
    {return;}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = root;
    }
}

node* Pop(Stack *ptr)
{
    if(isEmpty(ptr)==1)  //stack underflow
    {return NULL;}
    else
    {
        node* head = ptr->arr[ptr->top];
        ptr->arr[ptr->top] = NULL;
        ptr->top--;
        return head;
    }
}

node* Peek(Stack ptr)   //returns top value
{
    if(isEmpty(&ptr))
    {return NULL;}
    else
    {return ptr.arr[ptr.top];}   
}


/*QUEUE DEFINITION AND FUNCTIONS*/

//Linked list representation of queue of nodes
typedef struct qnode
{
    node* root;
    struct qnode* next;
}qnode;

typedef struct queue
{
    qnode* front;
    qnode* rear;
}queue;

//Queue operations for node queue
void initialize_queue(queue* q1)
{
    q1->rear = NULL;
    q1->front = NULL;
    return;
}

int isempty(queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        return 1;
    else
        return 0;
}

void enqueue(queue* q,node* root)  //enqueue at rear (last node)
{
    qnode* new_node = (qnode*)malloc(sizeof(qnode));  //intialize new node
    new_node->root = root;
    new_node->next = NULL;

    if(isempty(q))  //enqueue 1st node
    {
        q->rear = new_node;
        q->front = new_node;
        return;
    }
    q->rear->next = new_node;  //for all further nodes
    q->rear = new_node;
}

node* dequeue(queue* q)   //dequeue at front (head node)
{
    if(q->front==NULL)
    {return NULL;}
    
    qnode* temp = q->front;
    node* data = temp->root;
    q->front = q->front->next;
    free(temp);
    return data;
}

node* peek_front(queue* q)
{
    if(q->front==NULL)
    {return NULL;}
    return q->front->root;
}

void queue_traversal(queue q)
{
    qnode* ptr;
    ptr = q.front;
    while(ptr!=NULL)  //traverse until end
    {
        printf("%d ",ptr->root->data);
        ptr = ptr->next;
    }
    printf("\n");
}


/*NODE COUNTING PROBLEMS*/

//count total number of nodes (recursive)
int count_nodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

//count total number of nodes (using stack)
int Count_nodes(node* root)
{
    int count = 0;
    node* current = root;
    Stack s1;
    Stack_initialize(&s1,100);
    int done = 0;
    Push(&s1,current);
    while (isEmpty(&s1)!=1)
    {
        current = Pop(&s1);
        count++;
        if(current->left!=NULL)
        {
            Push(&s1,current->left);
        }
        if(current->right!=NULL)
        {
            Push(&s1,current->right);
        }
    }
    return count;
}

//count total number of nodes (using queue)  //NOT WORKING
int Count_Nodes(node* root)
{
    int count = 0;
    node* current = root;
    queue q1;
    initialize_queue(&q1);
    enqueue(&q1,root);
    while(isempty(&q1)!=1)
    {
        current = peek_front(&q1);
        //printf("%d ",current->data);
        count++;
        printf("%d ",count);
        if(current->left!=NULL)
        {
            enqueue(&q1,current->left);
        }
        if(current->right!=NULL)
        {
            enqueue(&q1,current->right);
        }
        dequeue(&q1);
    }
    return count;
}

//count no of leaf nodes
int count_leaf_nodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->left==NULL && root->right==NULL)
    {
        return 1;
    }
    return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

//count no of internal nodes   //NOT WORKING
int count_internal_nodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->left != NULL && root->right != NULL)
    {
        return 1;
    }
    return count_internal_nodes(root->left) + count_internal_nodes(root->right);
}

//check if tree is full
int isFullTree(node* root) //full tree = each node has either 0 or 2 children
{
    if(root==NULL)
    {
        return 1;
    }
    if(root->left==NULL && root->right==NULL)
    {
        return 1;
    }
    if((root->left==NULL && root->right!=NULL) || (root->left!=NULL && root->right==NULL) )
    {
        return 0;
    }
    return isFullTree(root->left) && isFullTree(root->right);
}

//inorder without recursion
void iterative_InOrder(node* root)
{
    node* current = root;
    int done = 0;
    Stack s1;
    Stack_initialize(&s1,100);
    while (done!=1)
    {
        if(current!=NULL)
        {
            Push(&s1,current);
            current = current->left;
        }
        else
        {
            if(isEmpty(&s1)!=1)
            {
                current = Pop(&s1);
                printf("%d ",current->data);
                current = current->right;
            }
            else
            {
                done = 1;
            }
        }
    }
}

//preporder without recursion
void iterative_PreOrder(node* root)
{
    node* current = root;
    int done = 0;
    Stack s1;
    Stack_initialize(&s1,100);
    while(done!=1)
    {
        if(current!=NULL)
        {
            printf("%d ",current->data);
            Push(&s1,current);
            current = current->left;
        }
        else
        {
            if(isEmpty(&s1)!=1)
            {
                current = Pop(&s1);
                current = current->right;
            }
            else
            {
                done = 1;
            }
        }
    }
}

//postorder without recursion   //NOT WORKING
void iterative_PostOrder(node* root)
{
    node* current = root;
    int done = 0;
    Stack s1;
    Stack_initialize(&s1,100);
    while(done!=1)
    {
        if(current!=NULL)
        {
            Push(&s1,current);
            current = current->left;
        }
        else
        {
            if(isEmpty(&s1)!=1)
            {
                current = Pop(&s1);
                //current = Peek(s1);
                if(current->right == NULL)
                {
                    printf("%d ",current->data);
                    //Pop(&s1);
                }
                current = current->right;
            }
            else
            {
                done = 1;
            }
        }
    }
}


//level order traversal using queue
void LevelOrder(node* root)
{
    node* current = root;
    queue q1;
    initialize_queue(&q1);
    enqueue(&q1,root);
    while(isempty(&q1)!=1)
    {
        current = peek_front(&q1);
        printf("%d ",current->data);
        if(current->left!=NULL)
        {
            enqueue(&q1,current->left);
        }
        if(current->right!=NULL)
        {
            enqueue(&q1,current->right);
        }
        dequeue(&q1);
    }
}


//find height of tree
int max(int a,int b)
{
    if(a > b)
        return a;
    else 
        return b;
}
int height(node* root)
{
    if(root==NULL)
    {
        return -1;
    }
    return 1 + max(height(root->left),height(root->right));
}

//find mirror image of the tree

//find root to node path
//find ancestors of a given node

//construct BT from given preorder + inorder
//construct BT from given postorder + inorder
//construct BT from given preorder + postorder 


int main()
{
    node* root = NULL;
    root = create_node(8);
    Insert(root,3);
    Insert(root,10); 
    Insert(root,1); 
    Insert(root,6); 
    Insert(root,4);
    Insert(root,5);
    Insert(root,7);
    Insert(root,100);
    InOrder(root);
    printf("\n");
    //iterative_PostOrder(root);
    printf("ans: %d ",Count_Nodes(root));
    //printf("ans: %d ",count_internal_nodes(root));
    LevelOrder(root);

    /*queue q1;
    node* root1 = create_node(10);
    node* root2 = create_node(20);
    node* root3 = create_node(30);
    node* root4 = create_node(40);
    node* root5 = create_node(50);
    initialize_queue(&q1);
    enqueue(&q1,root1);
    enqueue(&q1,root2);
    enqueue(&q1,root3);
    enqueue(&q1,root4);
    enqueue(&q1,root5);
    node* temp = dequeue(&q1);
    //printf("%d ",temp->data);
    //dequeue(&q1);
    //dequeue(&q1);
    //enqueue(&q1,root1);
    //enqueue(&q1,root3);
    //enqueue(&q1,root4);
    //node* temp = dequeue(&q1);
    //dequeue(&q1);
    printf("%d ",peek_front(&q1)->data);*/
 

    return 0;
}
