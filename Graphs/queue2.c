/*queue2 USING LINKED LIST*/
#include <stdio.h>
#include <stdlib.h>
#include "queue2.h"

queue2* initialize_queue2()
{
    queue2* q1 = (queue2*)malloc(sizeof(queue2));
    q1->rear = NULL;
    q1->front = NULL;
    return q1;
}

int isEmpty(queue2 *q)
{
    if(q->front==NULL)
        return 1;
    else
        return 0;
}

void enqueue2(queue2* q,int curr,int parent)  //enqueue2 at rear (last node)
{
    qnode2* new_node = (qnode2*)malloc(sizeof(qnode2));  //intialize new node
    new_node->curr = curr;
    new_node->parent = parent;
    new_node->next = NULL;

    if(isEmpty(q))  //enqueue2 1st node
    {
        q->rear = new_node;
        q->front = new_node;
        return;
    }
    q->rear->next = new_node;  //for all further nodes
    q->rear = new_node;
}

void dequeue2(queue2* q)   //dequeue2 at front (head node)
{
    if(q->front==NULL)
    {return;}
    
    qnode2* temp = q->front;
    q->front = q->front->next;
    if(q->front==NULL)
    {
        q->rear = NULL;
    }
    free(temp);
}

qnode2* peekFront(queue2* q)
{
    return q->front;
}

void displayqueue2(queue2 q)
{
    qnode2* ptr;
    ptr = q.front;
    while(ptr!=NULL)  //traverse until end
    {
        printf("%d ",ptr->curr);
        ptr = ptr->next;
    }
    printf("\n");
}