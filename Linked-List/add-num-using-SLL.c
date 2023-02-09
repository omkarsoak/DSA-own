/*ADDING TWO NUMBERS USING LINKED LIST*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}node;

typedef node* list;

void insert_at_begining(node** head_ref, int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void traverse_list(node* head)
{
    while (head != NULL) {
        printf("%d  ",head->data);
        head = head->next;
    }
    printf("\n");
}

node* add_Two_Lists(node** first_ref, node** second_ref)
{
    // result is head node of the resultant list
    node* first = *first_ref;
    node* second = *second_ref;
    node* result = NULL;
    int carry = 0, sum;
 
    // while both lists exist
    while (first != NULL || second != NULL) 
    {
        int s1,s2;

        //Conditions for unequal length of lists

        if(first!=NULL)
        {s1 = first->data;}
        else
        {s1 = 0;}
        if(second!=NULL)
        {s2 = second->data;}
        else
        {s2 = 0;}

        sum = carry + s1 + s2;
        // update carry for next calculation
        if(sum>=10)
        {carry = 1;}
        else 
        {carry = 0;}
        // update sum if it is greater than 10
        sum = sum % 10;
        insert_at_begining(&result,sum);  //push to result LL

        //update lists pointers only if they are not NULL
        if(first!=NULL)
            first = first->next;
        if(second!=NULL)
            second = second->next;
    }
    //add another node to result if last sum has a carry
    if(carry!=0)
    {
        insert_at_begining(&result,carry);
    }
    return result;
}

void reverse_list(node** head_ref)
{
    node* prev = NULL;
    node* current = *head_ref;
    node* next = NULL;
    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

int main()
{
    list L1 = NULL;
    list L2 = NULL;
    node* result;
    insert_at_begining(&L1,3);
    insert_at_begining(&L1,2);
    insert_at_begining(&L1,8);
    insert_at_begining(&L1,4);
    //insert_at_begining(&L1,2);

    insert_at_begining(&L2,9);
    insert_at_begining(&L2,1);
    insert_at_begining(&L2,0);
    insert_at_begining(&L2,3);
    insert_at_begining(&L2,4);

    result = add_Two_Lists(&L1,&L2);

    reverse_list(&L1);
    traverse_list(L1);

    reverse_list(&L2);
    traverse_list(L2);

    traverse_list(result);
    return 0;
}