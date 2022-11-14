#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};

void front_traversal(struct node* head)
{
    struct node* ptr= head;
    while(ptr!=NULL)
    {
        printf("%d\n",ptr->data);
        ptr = ptr->next;
    }
}

void back_transversal(struct node* fourth)
{
    struct node* ptr = fourth;
    while(ptr!=NULL)
    {
        printf("%d\n",ptr->data);
        ptr = ptr->prev;
    }
}

int main()
{
    //creating nodes
    struct node* head = (struct node*)malloc(sizeof(struct node));
    struct node* second = (struct node*)malloc(sizeof(struct node));
    struct node* third = (struct node*)malloc(sizeof(struct node));
    struct node* fourth = (struct node*)malloc(sizeof(struct node));

    //linking nodes
    head->data = 11;
    head->prev = NULL;
    head->next = second;

    second->data = 23;
    second->prev = head;
    second->next = third;

    third->data = 45;
    third->prev = second;
    third->next = fourth;

    fourth->data = 76;
    fourth->prev = third;
    fourth->next = NULL;

    //printf("success\n");
    front_traversal(head);
    printf("\n");
    back_transversal(fourth);
    return 0;
}