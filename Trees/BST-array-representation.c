/*******************
BST using arrays
FUNCTIONS:
- Insert
- Delete
- Search
- InOrder traversal
- Level order traversal (using queue)
- Height
- isComplete
- Count leaf nodes
*********************/
#include <stdio.h>
#include <stdlib.h>

typedef struct BST
{
    int* arr;
    int size;  //last index of element
}BST;

void BST_init(BST *t)
{
    t->arr = NULL;
    t->size = 0;
    return;
}

int search(BST t, int key)
{
    int i=0;
    while(i < t.size)
    {
        if(key == t.arr[i])
            return 1;
        else if(key < t.arr[i])   //search left subtree
            i = 2*i + 1;
        else                      //search right subtree
            i = 2*i + 2;
    }
    return 0;
}

void insert(BST* t,int key)
{
    if(t->size == 0) //emptry tree case
    {
        t->arr = (int*)malloc(sizeof(int));
        t->arr[0] = key;
        t->size++;
        return;
    }
    
    int p = 0; //position: goes from root(0) until location is found
    while(p < t->size && t->arr[p] != -1)   //-1 for empty spaces
    {
        if(t->arr[p] == key)  //duplicate
        {
            return;
        }
        if(key < t->arr[p])  //left subtree
            p = 2*p + 1;
        else                 //right subtree
            p = 2*p + 2;
    }
    
    if(p < t->size && t->arr[p]==-1)  //correct place found within current arr size
    {
        t->arr[p] = key;
        return;
    }

    //p > t->size
    t->arr = realloc(t->arr,(p+1)*sizeof(int));    
    for(int i = t->size; i<=p; i++)   //set all unused places to -1
    {
        t->arr[i] = -1;
    }
    t->arr[p] = key;   //insert at correct place
    t->size = p+1;
}

void delete(BST* t,int key)   //Incomplete
{
    int p = 0; //position: goes from root(0) until location is found
    while(p < t->size && t->arr[p] != -1)   //-1 for empty spaces
    {
        if(key < t->arr[p])        //left subtree
            p = 2*p + 1;
        else if(key > t->arr[p])   //right subtree
            p = 2*p + 2;
        else                      //element to be deleted found
            break;
    }
    //Case 1: Leaf node (no children)
    if((t->arr[2*p+1]==-1 || 2*p+1 > t->size) && (t->arr[2*p+2]==-1 || 2*p+2 > t->size))
    {
        t->arr[p] = -1;
        return;
    }
    //case 2: Node with 1 child
    if((t->arr[2*p+1]==-1 || 2*p+1 > t->size) && (t->arr[2*p+2]!=-1))  //only right child
    {
        int parent = (p - 1)/2;
        if(t->arr[p] > t->arr[parent])   //right of right child case
        {
            t->arr[p] = t->arr[2*p+2];
            t->arr[2*p+1] = -1;
            return;
        }
        else
        {

        }
    }
    else if((t->arr[2*p+1]!=-1) && (t->arr[2*p+2]==-1 || 2*p+2 > t->size))  //only left child
    {

    }
    //case 3: Node with 2 children

    return;

}

//find height of tree
int max(int a,int b)
{
    if(a > b)
        return a;
    else 
        return b;
}
int height(BST t,int p)
{
    if(t.arr[p]==-1 || p > t.size)
    {
        return -1;
    }
    return 1 + max(height(t,2*p+1),height(t,2*p+2));
}


int isComplete(BST t)    
{
    //if we find consecutive -1s, it is not complete
	for (int i = 0; i < t.size-1; i++)   
	{
		if (t.arr[i] == -1 && t.arr[i+1] != -1)
		{
			return 0;
		}
	}
	return 1;
}

/*QUEUE DEFINITON AND FUNCTIONS*/
//It is a circular queue with array implementation
typedef struct queue{
    int capacity;   //size of total array
    int size;   //size of array at any given moment
    int front;  //front: DEQUEUE
    int rear;  //back: ENQUEUE
    int *arr;
}queue;

queue* initialize_queue(int capacity)
{
    queue* q = (queue*)malloc(sizeof(queue));
    q->capacity = capacity;
    q->front = -1;   //initially both front and rear = -1
    q->rear = -1;
    q->size = 0;
    q->arr = (int*)malloc(q->capacity*sizeof(int));
    return q;
}

int isFull(queue* q)
{
    if(q->size == q->capacity)
        return 1;
    else
        return 0;
}

int isEmpty(queue* q)
{
    if(q->size == 0)
        return 1;
    else
        return 0;
}

void enqueue(queue* q,int data)  //insertion at rear
{
    if(isFull(q)==1)
    {return;}

    if(q->front==-1)   //condition for 1st enqueue (corner case)
    {
        q->front = 0;
    }
    q->rear = (q->rear+1)% q->capacity;   
    //using modulo operator so that, if rear reaches capacity, it goes back to 0
    q->arr[q->rear] = data;
    q->size++;
}

int dequeue(queue* q)   //deletion at front
{
    if(isEmpty(q)==1)
    {
        return -1;
    }
    if(q->front==q->rear)
    {
        if(q->size!=0)
            q->size = 0;
        return -1;
    }
    int data = q->arr[q->front];
    q->front=(q->front+1)% q->capacity;
    //using modulo operator so that, if front reaches capacity, it goes back to 0
    q->size--;
    return data;
}

int peek_front(queue* q)
{
    if(isEmpty(q)==1)
        return -2;
    else
        return q->arr[q->front];
}

void queue_traversal(queue* q)
{
    for(int i=0;i<q->size;i++)
    {
        printf("%d ",q->arr[i]);
    }
    printf("\n");
}

//level order traversal using queue
void levelOrder(BST t)
{
    int p = 0;
    queue* q1 = initialize_queue(100);
    enqueue(q1,p);   //enqueue root
    while(isEmpty(q1)!=1)
    {
        p = peek_front(q1);
        printf("%d ",t.arr[p]);
        if(t.arr[2*p+1]!=-1 && 2*p+1 < t.size)   //if left child exists
        {
            enqueue(q1,2*p+1);   //enqueue left child
        }
        if(t.arr[2*p+2]!=-1 && 2*p+2 < t.size)  //if right child exists
        {
            enqueue(q1,2*p+2);   //enqueue right child
        }
        dequeue(q1);
    }
}

int Count_leaf_nodes(BST t)
{
    //same as level order traversal
    int p = 0;
    int count = 1;
    queue* q1 = initialize_queue(100);
    enqueue(q1,p); 
    while(isEmpty(q1)!=1)
    {
        p = peek_front(q1);
        //check if leaf node
        if((t.arr[2*p+1]==-1 || 2*p+1 > t.size) && (t.arr[2*p+2]==-1 || 2*p+2 > t.size) ) 
        {
            count++;
        }
        if(t.arr[2*p+1]!=-1 && 2*p+1 < t.size)
        {
            enqueue(q1,2*p+1);
        }
        if(t.arr[2*p+2]!=-1 && 2*p+2 < t.size)
        {
            enqueue(q1,2*p+2);
        }
        dequeue(q1);
    }
    return count;
}

void inorder_helper(BST t,int p)
{
    if(p >= t.size || t.arr[p] == -1)  //exit condition
    {
        return;
    }
    inorder_helper(t,(2*p + 1));  //left subtree
    printf("%d ",t.arr[p]);
    inorder_helper(t,(2*p + 2));  //right subtree
}

void Inorder(BST t)
{
    inorder_helper(t,0);
    return;
}

void print_array(BST t)
{
    for(int i=0;i < t.size;i++)
    {
        printf("%d ",t.arr[i]);
    }
    printf("\n");
}

int main()
{
    BST t1;
    BST_init(&t1);
    insert(&t1,8);
    insert(&t1,3);
    insert(&t1,10);
    insert(&t1,1);
    insert(&t1,6);
    insert(&t1,4);
    insert(&t1,5);
    insert(&t1,7);
    insert(&t1,100);
    Inorder(t1);
    printf("\n");
    //printf("complete: %d ",isComplete(t1));
    //print_array(t1);
    //printf("Search: %d ",search(t1,44));
    //printf("Height: %d ",height(t1,0));
    levelOrder(t1);
    printf("count: %d ",Count_leaf_nodes(t1));

    return 0;
}