/*STACK USING ARRAY*/
#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int size;
    int top;
    int *arr;
}stack;

void stack_initialize(stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->arr = (int*)malloc(s->size*sizeof(int));
}

int isempty(stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int isfull(stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;} 
}

void stack_traversal(stack *ptr)
{
    for(int i=0;i<=ptr->top;i++)
    {
        printf("%d ",ptr->arr[i]);
    }
    printf("\n");
}

void push(stack *ptr,int data)
{
    if(isfull(ptr)==1)  //stack overflow
    {return;}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = data;
    }
}

int pop(stack *ptr)
{
    if(isempty(ptr)==1)  //stack underflow
    {return -1;}
    else
    {
        int data = ptr->arr[ptr->top];
        ptr->top--;
        return data;
    }
}

int peek(stack ptr)   //returns top value
{
    if(isempty(&ptr))
    {return -1;}
    else
    {return ptr.arr[ptr.top];}   
}

int main()
{
    stack s1;
    stack_initialize(&s1,10);
    push(&s1,10);
    push(&s1,12);
    push(&s1,11);
    push(&s1,13);
    push(&s1,15);
    printf("peek: %d\n",peek(s1));
    stack_traversal(&s1);
    printf("poped from the stack: %d\n",pop(&s1));
    stack_traversal(&s1);
    printf("Stack top is: %d\n",peek(s1));
    return 0;
}
