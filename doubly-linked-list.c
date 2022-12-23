#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* prev;
    struct node* next;
}node;

void front_traversal(node* head)
{
    node* ptr= head;
    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void back_transversal(node* last)
{
    node* ptr = last;
    while(ptr!=NULL)
    {
        printf("%d ",ptr->data);
        ptr = ptr->prev;
    }
    printf("\n");
}

void insert_at_begining(node** head_ref,int data)
{
    node* new_node = (node*)malloc(sizeof(node));  
    new_node->data = data;
    new_node->next = (*head_ref);  //new_node->next points to head
    new_node->prev = NULL;   //as first node->prev always points to null
    if(*head_ref!=NULL)
    {
        (*head_ref)->prev =  new_node->prev;
    }
    (*head_ref) = new_node;  //head points to new_node
}

int main()
{
    node* head = NULL;
    insert_at_begining(&head,3);
    insert_at_begining(&head,2);
    insert_at_begining(&head,4);
    insert_at_begining(&head,5);
    front_traversal(head);
    back_transversal(head->next->next);
    return 0;
}