/*CIRCULAR QUEUE IMPLEMENTATION USING ARRAY
 METHODS:
 1. INITIALIZE
 2. ENQUEUE
 3. DEQUEUE
 4. isfull() , isempty()
 5. peek_front() , peek_rear()
 6. DISPLAY
*/
#include <stdio.h>
#include <stdlib.h>
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
    if(isEmpty(q))
    {
        return -1;
    }
    return q->arr[q->front];
}

int peek_rear(queue* q)
{
    if(isEmpty(q))
    {
        return -1;
    }
    return q->arr[q->rear];
}

void display_queue(queue* q)
{
    if(isEmpty(q))
    {
        return;
    }

    //normal case
    if(q->front < q->rear) 
    {
        for(int i=q->front;i<=q->rear;i++)
        {
            printf("%d ",q->arr[i]);
        }
    }
    //case after atleast one cycle i.e rear has gone to 0 after exceeding capacity
    else if(q->front > q->rear)   
    {
        for(int i=q->front;i<q->capacity;i++)
        {
            printf("%d ",q->arr[i]);
        }
        for(int i=0;i<=q->rear;i++)
        {
            printf("%d ",q->arr[i]);
        }
    }
    printf("\n");
}

int main()
{
    queue* q = initialize_queue(5);
    enqueue(q,10);
    enqueue(q,20);
    enqueue(q,30);
    enqueue(q,40);
    enqueue(q,50);
    display_queue(q);
    printf("Front:%d Rear:%d Size:%d\n",q->front,q->rear,q->size);
    printf("Dequeued: %d\n",dequeue(q));
    enqueue(q,60);
    enqueue(q,70);
    display_queue(q);
    printf("Front:%d Rear:%d Size:%d\n",q->front,q->rear,q->size);
    printf("Peek: rear:%d front:%d\n",peek_rear(q),peek_front(q));
    return 0;
}
