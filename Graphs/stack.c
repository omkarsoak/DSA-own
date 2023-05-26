/*STACK USING LINKED LIST*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void displayStack(snode* ptr)
{
    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int is_empty(snode* top)
{
    if(top==NULL)
    {return 1;}
    else
    {return 0;}
}

int is_full(snode* top)
{
    snode* n = (snode*)malloc(sizeof(snode));
    if(n==NULL)
    {return 1;}
    else
    {return 0;}
}

void push(snode** top,int data)
{
    if(is_full(*top)==1)
    {return;}
    else
    {
        snode* n = (snode*)malloc(sizeof(snode));
        n->data = data;
        n->next = *top;
        *top = n;
    }
}

int pop(snode** top)
{
    if(is_empty(*top)==1)
    {return -1;}

    snode* temp = *top;
    int data = (*top)->data;
    (*top) = (*top)->next;
    free(temp);
    return data;
    
}

int peek(snode* top)  //returns the data at the top
{
    snode* ptr = top;
    if(ptr!=NULL)
    {
        return ptr->data;
    }
    else 
    {return -1;}
}