/*QUEUE USING STACK (DEQUEUE COSTLY)
ENQUEUE: O(1)
- PUSH TO STACK1
DEQUEUE: worst case:O(n), avg case: O(1)
- if stack2 is empty, push everything from stack1 to stack2
- Pop the element from stack2 and return it
- DO NOT push everything back to stack1 (LET IT REMAIN AS IT IS)
- Whenever, stack2 will get empty, in the next operation, 
  push everything from stack1 to stack2 and the cycle continues
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef node* stack;

typedef struct queue
{
    stack s1;
    stack s2;
}queue;

/*STACK FUNCTIONS*/
void linked_list_traversal(node* ptr)
{
    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int is_empty(node* top)
{
    if(top==NULL)
    {return 1;}
    else
    {return 0;}
}

int is_full(node* top)
{
    node* n = (node*)malloc(sizeof(node));
    if(n==NULL)
    {return 1;}
    else
    {return 0;}
}

void push(node** top,int data)
{
    if(is_full(*top)==1)
    {printf("Stack overflow\n");}
    else
    {
        node* n = (node*)malloc(sizeof(node));
        n->data = data;
        n->next = *top;
        *top = n;
    }
}

int pop(node** top)
{
    if(is_empty(*top)==1)
    {printf("Stack underflow\n");}
    else
    {
        node* top1 = *top;
        int data = top1->data;
        top1 = top1->next;
        free(top);
        *top = top1;
        return data;
    }
}

/*QUEUE FUNCTIONS*/
void enqueue(queue* q,int data)
{
    push(&(q->s1),data);  
}

int dequeue(queue* q)
{
    //Move elements from stack1 to stack 2 only if stack2 is empty
    if(is_empty(q->s2))
    {
        while(is_empty(q->s1)!=1)
        {
            //pushing to stack2
            int temp = pop(&(q->s1));
            push(&(q->s2),temp);
        }
    }
    int data = pop(&(q->s2));  //pop last element from stack2
    return data;
}

int main()
{
    queue q1;
    q1.s1 = NULL;
    q1.s2 = NULL;
    enqueue(&q1,10);
    enqueue(&q1,20);
    enqueue(&q1,30);
    enqueue(&q1,40);
    enqueue(&q1,50);
    linked_list_traversal(q1.s1);
    printf("dequeue: %d\n",dequeue(&q1));
    printf("dequeue: %d\n",dequeue(&q1));
    printf("dequeue: %d\n",dequeue(&q1));
    enqueue(&q1,60);
    printf("Stack1:");
    linked_list_traversal(q1.s1);
    printf("Stack2:");
    linked_list_traversal(q1.s2);

    return 0;
}