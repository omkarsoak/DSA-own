#include <stdio.h>
#include <stdlib.h>
/*******Linked list functions & definition**********/
typedef struct node
{
    int data;
    struct node* next;
}node;

//Linked list functions
void insert_at_begining(node** head_ref, int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
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

void traverse_list(node* head)
{
    while (head != NULL) {
        printf("%d  ",head->data);
        head = head->next;
    }
    printf("\n");
}

int reverse_list(node** head_ref)  //reverses list & returns size of list
{
    node* prev = NULL;
    node* current = *head_ref;
    node* next = NULL;
    int length = 0;
    while (current != NULL) 
    {
        length++;
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
    return length;
}

node* create_new_node(int data) 
{
    node* nn = (node*)malloc(sizeof(node));
    nn->data = data;
    nn->next = NULL;
    return nn;
}