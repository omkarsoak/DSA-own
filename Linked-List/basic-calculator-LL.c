/*****************
BASIC CALCULATOR :
INPUT: STRING OF NUMBERS AND '+' IN BETWEEN 
OUPUT: ANSWER
EXAMPLE:
198237918479+83634875862
Num 1: 1  9  8  2  3  7  9  1  8  4  7  9
Num 2: 8  3  6  3  4  8  7  5  8  6  2
Answer: 2  8  1  8  7  2  7  9  4  3  4  1
****************/
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

void convert_to_list(node** head_ref)
{
    char x='0';
    int y=0;
    while(x!='+')
    {
        scanf("%c",&x);
        y = x - '0';
        if(y>=0 && y<=9)
            insert_at_begining(head_ref,y);
        else
            break;
    }
}

int main()
{
    node* head1 = NULL;
    node* head2 = NULL;
    node* result;
    printf("Enter the calculation:\n");
    convert_to_list(&head1);
    convert_to_list(&head2);
    result = add_Two_Lists(&head1,&head2);
    
    printf("Num 1: ");
    reverse_list(&head1);
    traverse_list(head1);
    printf("Num 2: ");
    reverse_list(&head2);
    traverse_list(head2);

    printf("Answer: ");
    traverse_list(result);
    return 0;
}