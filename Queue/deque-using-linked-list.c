/*DEQUE USING LINKED LIST
DOUBLE ENDED QUEUE
- INSERT AT REAR
- INSERT AT FRONT
- DELETE AT REAR
- DELETE AT FRONT
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}node;

typedef struct queue
{
    node* front;
    node* rear;
}queue;

void initialize_queue(queue* q1)
{
    q1->rear = NULL;
    q1->front = NULL;
    return;
}

int isEmpty(queue *q)
{
    if(q->front==NULL || q->rear==NULL)
        return 1;
    else
        return 0;
}

void insertRear(queue* q,int data)  //enqueue at rear (last node)
{
    node* new_node = (node*)malloc(sizeof(node));  //intialize new node
    new_node->data = data;
    new_node->next = NULL;

    if(isEmpty(q))  //enqueue 1st node
    {
        q->rear = new_node;
        q->front = new_node;
        return;
    }
    q->rear->next = new_node;  //for all further nodes
    q->rear = new_node;
}

void insertFront(queue* q,int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    if(isEmpty(q))  //enqueue 1st node
    {
        q->rear = new_node;
        q->front = new_node;
        return;
    }
    new_node->next = q->front;
    q->front = new_node;
}

int deleteFront(queue* q)   //dequeue at front (head node)
{
    if(q->front==NULL)
    {return -1;}
    
    node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    free(temp);
    return data;
}

int deleteRear(queue* q)
{
    if(q->front==NULL)
    {return -1;}

    node* temp = q->rear;
    int data = temp->data;
    
}

void displayQueue(queue q)
{
    node* ptr;
    ptr = q.front;
    while(ptr!=NULL)  //traverse until end
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    queue q;
    initialize_queue(&q);
    insertRear(&q,10);
    insertRear(&q,20);
    insertRear(&q,30);
    insertRear(&q,40);
    insertRear(&q,50);
    deleteFront(&q);
    insertFront(&q,60);
    displayQueue(q);

    return 0;
}
