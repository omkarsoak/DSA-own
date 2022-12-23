#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}node;
typedef node* list;

void insert_at_begining(node** head_ref,int data)
{
    node* new_node = (node*)malloc(sizeof(node));  
    new_node->data = data;
    new_node->next = (*head_ref);  //new_node->next points to head
    (*head_ref) = new_node;  //head points to new_node
}

void insert_at_end(node** head_ref,int data)
{
    node* new_node = (node*)malloc(sizeof(node));  //create node to be added
    new_node->data = data;
    new_node->next = NULL;
    if (*head_ref == NULL)  //checking if list is empty
    {
       *head_ref = new_node;
       return;
    } 
    node* p = *head_ref;  //traversal node
    while(p->next!=NULL)  //traverse list until last element
    {
        p = p->next;
    }
    p->next = new_node;
}

void insert_after(node* prev_node,int data)
{
    node* new_node = (node*)malloc(sizeof(node)); //create node to be added
    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void insert_between(node** head_ref,int data,int index)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    node* p = *head_ref;
    for(int i=0;i<index-1;i++)  //traverse list until index-1
    {
        p = p->next;
    }
    new_node->next = p->next;  //add node
    p->next = new_node;
}

void linked_list_traversal(node*ptr)
{
    while(ptr!=NULL)  //traverse until end
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void delete_node_atValue(node** head_ref,int value)
{
    node* p = *head_ref;  
    node* q = (*head_ref)->next;  //q is 1 node ahead of p
    while(q->data!=value)
    {
        p=p->next;
        q=q->next;
    }
    p->next = q->next;  //remove connection
    free(q);   //free pointer
}

void delete_node_atIndex(node** head_ref,int index)
{
    node* p = *head_ref;
    node* q = (*head_ref)->next;
    int i=0;
    while(i < index-1)  //traverse until index-1
    {
        p=p->next;
        q=q->next;
        i++; 
    }
    p->next = q->next;  //remove connectipn
    free(q);   //free pointer
}

void reverse_list(node** head_ref)
{
    node* prev = NULL;
    node* curr = *head_ref;
    node* next = NULL;
    while(curr!=NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        (*head_ref) = prev;
    }
}

int main()
{
    node* head = NULL;
    insert_at_end(&head,10);
    insert_at_end(&head,20);
    insert_at_end(&head,30);
    insert_at_end(&head,40);
    insert_at_end(&head,50);
    insert_after(head->next->next,33);
    insert_between(&head,88,3);
    delete_node_atIndex(&head,3);
    delete_node_atValue(&head,20);
    reverse_list(&head);
    linked_list_traversal(head);
    return 0;
}