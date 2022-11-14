#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};
void linked_list_traversal(struct node* ptr)
//ptr is a pointer of struct node* type, thus we use it to traverse the linked list
{
    while(ptr!=NULL)
    {
        printf("Element is: %d\n",ptr->data);
        ptr = ptr->next;
    }
}

struct node* insert_at_first(struct node* head, int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = head;
    return ptr;
}

struct node* insert_between(struct node* head,int data, int index)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    struct node* p = head;
    int i=0;
    while(i!=index-1)
    {
        p = p->next;
        i++;
    }
    ptr->data = data;
    ptr->next = p->next;
    p->next = ptr;
    return head;
}

struct node* insert_at_end(struct node* head, int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;

    struct node* p = head;
    while(p->next!=NULL)
    {
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;
    return head;
}

struct node* insert_after_node(struct node* head, struct node* prev_node, int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;

    ptr->next = prev_node->next;
    prev_node->next = ptr;
    return head;
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
    fourth->next = NULL;

    linked_list_traversal(head);
    printf("\n");
    head = insert_at_first(head,23);
    linked_list_traversal(head);
    printf("\n");
    head = insert_between(head,34,3);
    linked_list_traversal(head);
    printf("\n");
    head = insert_at_end(head,56);
    linked_list_traversal(head);
    printf("\n");
    head = insert_after_node(head,second,12);
    linked_list_traversal(head);

    return 0;
}