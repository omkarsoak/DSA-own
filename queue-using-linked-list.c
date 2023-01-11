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
    if(q->front==NULL && q->rear==NULL)
        return 1;
    else
        return 0;
}

void enqueue(queue* q,int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(!new_node)
        return;
    new_node->data = data;
    new_node->next = NULL;
    if(isEmpty(q))
    {
        q->rear = new_node;
        q->front = new_node;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
}

int dequeue(queue* q)
{
    if(q->front==NULL)
    {return -1;}
    
    node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
		q->rear = NULL;
    free(temp);
    return data;
}

void linked_list_traversal(queue q)
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
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    enqueue(&q,40);
    enqueue(&q,50);
    dequeue(&q);
    linked_list_traversal(q);

    return 0;
}
