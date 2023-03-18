#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
/********CHAR STACK DEFINITION & FUNCTIONS*******/
typedef struct stack
{
    int size;
    int top;
    char* arr;
}stack;

//stack operations
void stack_initialize(stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->arr = (char*)malloc(s->size*sizeof(char));
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

void push(stack *ptr,char data)
{
    if(isfull(ptr)==1)  //stack overflow
    {return;}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = data;
    }
}

char pop(stack *ptr)
{
    if(isempty(ptr)==1)  //stack underflow
    {return -1;}
    else
    {
        char data = ptr->arr[ptr->top];
        ptr->top--;
        return data;
    }
}

char peek(stack ptr)   //returns top value
{
    if(isempty(&ptr))
    {return -1;}
    else
    {return ptr.arr[ptr.top];}   
}

/*****NODE STACK DEFINTION & FUNCTIONS*******/
typedef struct Stack
{
    int size;
    int top;
    node** arr;
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