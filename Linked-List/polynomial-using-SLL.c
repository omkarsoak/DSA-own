/******
* POLYNOMIAL REPRESENTATION USING SINGLE LINKED LIST
* always create polynomial in decreasing order of degree
    example:
    4x^2 + 3x^1 + 2x^0 +
    9x^5 + 6x^4 + 5x^3 + 3x^1 + 2x^0
******/
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int coeff;
    int pow;
    struct node* next;
}node;

typedef node* polynomial;

void create_node(int coeff,int pow,node** head_ref)  //same as insert_at_begining in SLL
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->coeff = coeff;
    new_node->pow = pow;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

//Addition of two polynomials
node* poly_add(node** headref1, node** headref2)
{
    node* result = NULL;
    node* poly1 = (*headref1);
    node* poly2 = (*headref2);

    while(poly1!=NULL && poly2!=NULL)
    {
        if(poly1->pow == poly2->pow)
        {
            create_node(poly1->coeff + poly2->coeff ,poly1->pow ,&result);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        else if(poly1->pow > poly2->pow)
        {
            create_node(poly1->coeff,poly1->pow,&result);
            poly1 = poly1->next;
        }
        else if(poly2->pow > poly1->pow)
        {
            create_node(poly2->coeff,poly2->pow,&result);
            poly2 = poly2->next; 
        }
    }
  
    //dump remaining elements into result
    while (poly1!=NULL || poly2!=NULL)
    {
        if(poly1!=NULL)
        {
            create_node(poly1->coeff,poly1->pow,&result);
            poly1 = poly1->next;
        }

        if(poly2!=NULL)
        {
            create_node(poly2->coeff,poly2->pow,&result);
            poly2 = poly2->next;
        }
    }
    return result;
}

void linked_list_traversal(node*ptr)
{
    while(ptr!=NULL)  //traverse until end
    {
        printf("%dx^%d + ",ptr->coeff,ptr->pow);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    polynomial poly1 = NULL;
    create_node(2,0,&poly1);
    create_node(3,1,&poly1);
    create_node(4,2,&poly1);
    linked_list_traversal(poly1);

    polynomial poly2 = NULL;
    //create_node(1,0,&poly2);
    //create_node(2,1,&poly2);
    //create_node(3,2,&poly2);
    create_node(5,3,&poly2);
    create_node(6,4,&poly2);
    create_node(9,5,&poly2);
    linked_list_traversal(poly2);

    polynomial sum = NULL;
    sum = poly_add(&poly1,&poly2);
    linked_list_traversal(sum);
    return 0;
}