#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* prev;
    struct node* next;
}node;

typedef node* list;

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
    while(ptr->prev!=NULL)
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
    if((*head_ref)==NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        (*head_ref) = new_node;
        return;
    }

    (*head_ref)->prev = new_node;
    new_node->next = (*head_ref);  //new_node->next points to head
    new_node->prev = NULL;   //as first node->prev always points to null
    (*head_ref) = new_node;  //head points to new_node
}

void insert_at_end(node** head_ref,int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    if((*head_ref)==NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        (*head_ref) = new_node;
        return;
    }
    node* p = (*head_ref);
    while (p->next!=NULL)
    {
        p = p->next;
    }
    new_node->next = NULL;
    new_node->prev = p;
    p->next = new_node;
}



int main()
{
    node* head = NULL;
    insert_at_begining(&head,3);
    insert_at_begining(&head,2);
    insert_at_begining(&head,4);
    insert_at_begining(&head,5);
    insert_at_end(&head,10);
    front_traversal(head);
    return 0;
}
