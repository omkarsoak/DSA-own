/*QUEUE USING LINKED LIST*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue* initialize_queue()
{
    queue* q1 = (queue*)malloc(sizeof(queue));
    q1->rear = NULL;
    q1->front = NULL;
    return q1;
}

int isEmpty(queue *q)
{
    if(q->front==NULL || q->rear==NULL)
        return 1;
    else
        return 0;
}

void enqueue(queue* q,int data)  //enqueue at rear (last node)
{
    qnode* new_node = (qnode*)malloc(sizeof(qnode));  //intialize new node
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

void dequeue(queue* q)   //dequeue at front (head node)
{
    if(q->front==NULL)
    {return -1;}
    
    qnode* temp = q->front;
    q->front = q->front->next;
    free(temp);
}

qnode* peekFront(queue* q)
{
    return q->front;
}

void displayQueue(queue q)
{
    qnode* ptr;
    ptr = q.front;
    while(ptr!=NULL)  //traverse until end
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

