/*STACK USING LINKED LIST*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef node* stack;

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
        node* temp = *top;
        int data = (*top)->data;
        (*top) = (*top)->next;
        free(temp);
        return data;
    }
}

int peek(node* top)  //returns the data at the top
{
    node* ptr = top;
    if(ptr!=NULL)
    {
        return ptr->data;
    }
    else 
    {return -1;}
}

int main()
{
    stack s1 = NULL;
    push(&s1,10);
    push(&s1,20);
    push(&s1,30);
    push(&s1,40);
    push(&s1,50);
    linked_list_traversal(s1);
    
    pop(&s1);
    pop(&s1);
    linked_list_traversal(s1);
    printf("%d ",peek(s1));
    return 0;
}
