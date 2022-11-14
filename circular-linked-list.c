#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

void linked_list_transversal(struct node* head)
{
    struct node* ptr = head;
    do{
        printf("%d\n",ptr->data);
        ptr = ptr->next;
    } while(ptr!=head);
}

struct node* insert_at_first(struct node* head,int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    struct node* p = head->next;
    while(p->next!=head)
    {
        p = p->next;
    }
    p->next = ptr;
    ptr->next = head;
    return ptr;
}

int main()
{
    struct node *head;
    struct node *second;
    struct node *third;
    struct node *fourth;

    //Allocate memory for nodes in heap
    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third = (struct node*)malloc(sizeof(struct node));
    fourth = (struct node*)malloc(sizeof(struct node));

    //link 1st and 2nd nodes
    head->data = 7;
    head->next = second;
    //link 2nd and 3rd nodes
    second->data = 4;
    second->next = third;
    //terminate linked list
    third->data = 11;
    third->next = fourth;

    fourth->data = 24;
    fourth->next = head;

    linked_list_transversal(head);
    printf("\n");
    head = insert_at_first(head,3);
    linked_list_transversal(head);
    return 0;
}