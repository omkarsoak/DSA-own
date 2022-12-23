#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

void linked_list_transversal(node* head)
{
    node* ptr = head;
    do{
        printf("%d ",ptr->data);
        ptr = ptr->next;
    } while(ptr!=head);
    printf("\n");
}

void insert_at_first(node** head_ref,int data)
{
    node* ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    if((*head_ref)==NULL)   //condition for empty list
    {
        (*head_ref) = ptr;
        (*head_ref)->next = (*head_ref);
    }
    node* p = (*head_ref)->next;
    while(p->next!=(*head_ref))
    {
        p = p->next;
    }
    p->next = ptr;
    ptr->next = (*head_ref);
    (*head_ref) = ptr;
}

int main()
{
    node *head = NULL;
    insert_at_first(&head,3);
    insert_at_first(&head,4);
    insert_at_first(&head,5);
    insert_at_first(&head,6);
    insert_at_first(&head,7);
    linked_list_transversal(head);
    return 0;
}