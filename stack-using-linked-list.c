#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node* top=NULL;  
//here top is made global variable to avoid problems in pop() function

void linked_list_traversal(node* ptr)
{
    while(ptr!=NULL)
    {
        printf("Element is: %d\n",ptr->data);
        ptr = ptr->next;
    }
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

node* push(node* top,int data)
{
    if(is_full(top)==1)
    {printf("Stack overflow\n");}
    else
    {
        node* n = (node*)malloc(sizeof(node));
        n->data = data;
        n->next = top;
        top = n;
        return top;
    }
}

int pop(node* tp)
{
    if(is_empty(top)==1)
    {printf("Stack underflow\n");}
    else
    {
        node* n = tp;
        top = tp->next;
        int data = n->data;
        free(n);
        return data;
    }
}

int peek(node* top,int index)
{
    node* ptr = top;
    for(int i=0;(i<index-1 && ptr!=NULL);i++)
    {
        ptr = ptr->next;
    }
    if(ptr!=NULL)
    {
        return ptr->data;
    }
    else 
    {return -1;}
}

int stack_top(node* top)
{
    return top->data;
}

int stack_bottom(node* top)
{
    node* ptr = top;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
    return ptr->data;
}

int main()
{
    top = push(top,28);
    top = push(top,32);
    top = push(top,11);
    top = push(top,8);
    top = push(top,4);
    linked_list_traversal(top);
    printf("Element poped is: %d\n",pop(top));
    linked_list_traversal(top);
    printf("The element at index %d is: %d\n",2,peek(top,2));
    printf("Stack top is: %d\n",stack_top(top));
    printf("Stack bottom is: %d\n",stack_bottom(top));

    return 0;
}