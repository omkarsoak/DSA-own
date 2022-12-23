#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int size;
    int top;
    int *arr;
};

int isempty(struct stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int isfull(struct stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;}
    
}

void stack_traversal(struct stack *ptr)
{
    for(int i=0;i<=ptr->top;i++)
    {
        printf("%d\n",ptr->arr[i]);
    }
}

void push(struct stack *ptr,int data)
{
    if(isfull(ptr)==1)
    {printf("Stack overflow\n");}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = data;
    }
}

int pop(struct stack *ptr)
{
    if(isempty(ptr)==1)
    {
        printf("Stack underflow\n");
        return -1;
    }
    else
    {
        int data = ptr->arr[ptr->top];
        ptr->top--;
        return data;
    }
}

int peek(struct stack *ptr,int i)
{
    if((ptr->top-i+1)<0)
    {
        return -1;
    }
    else
    {
        return ptr->arr[ptr->top-i+1];
    }   
}

int stack_top(struct stack *ptr)
{
    return ptr->arr[ptr->top];
}

int stack_bottom(struct stack *ptr)
{
    return ptr->arr[0];
}

int main()
{
    struct stack *s;
    s->size = 10;
    s->top = -1;
    s->arr = (int*)malloc(s->size*sizeof(int));
    //push elements manually
    s->arr[0] = 4;
    s->top++;
    s->arr[1] = 22;
    s->top++;
    s->arr[2] = 31;
    s->top++;

    push(s,11);
    stack_traversal(s);
    printf("poped from the stack: %d\n",pop(s));
    stack_traversal(s);
    printf("Stack top is: %d\n",stack_top(s));
    printf("Stack bottom is: %d\n",stack_bottom(s));
    return 0;
}