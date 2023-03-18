#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
/********OPERATIONS*********/
//Add
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
    reverse_list(&result);
    return result;
}

//Subtract
int findLength(node* ptr)  //find length of LL
{
    int size = 0;
    while (ptr != NULL) 
    {
        ptr = ptr->next;
        size++;
    }
    return size;
}

node* paddZeros(node* snode, int diff)   //add zeros to the front to make length same
{
    if (snode == NULL)
        return NULL;
    
    while (diff!=0) 
    {
        insert_at_begining(&snode,0);
        diff--;
    }
    return snode;
}

static int borrow;
node* subtract_helper(node* l1,node* l2)
{
    if (l1 == NULL && l2 == NULL && borrow == 0)
        return NULL;

    node* previous = subtract_helper(l1 ? l1->next : NULL, l2 ? l2->next : NULL);
    int d1 = l1->data;
    int d2 = l2->data;
    int sub = 0;
  
    //if you have given the value to next digit then reduce the d1 by 1
    if (borrow) 
    {
        d1--;
        borrow = 0;
    }
  
    //If d1 < d2, then borrow the number from previous digit. Add 10 to d1 and set borrow = true;
    if (d1 < d2) 
    {
        borrow = 1;
        d1 = d1 + 10;
    }
  
    //subtract the digits
    sub = d1 - d2;
  
    //Create a node with sub value
    node* current = create_new_node(sub);
  
    //Set the Next pointer as Previous
    current->next = previous;

    return current;
}

node* subtract_Two_Lists(node** first_ref,node** second_ref)
{
    int num1Length = reverse_list(first_ref);
    int num2Length = reverse_list(second_ref);
    node* num1 = (*first_ref);
    node* num2 = (*second_ref);
    node* result;

    node *lnode = NULL, *snode = NULL;
    
    node* temp1 = num1;
    node* temp2 = num2;

    if(num1Length!=num2Length)
    {
        if(num1Length > num2Length)
        {
            lnode = num1; snode = num2;
        }
        else
        {
            lnode = num2; snode = num1;
        }
        snode = paddZeros(snode, abs(num1Length - num2Length));
    }
    else
    {
        while (num1 && num2) 
        {
            if (num1->data != num2->data) 
            {
                lnode = num1->data > num2->data ? temp1 : temp2;
                snode = num1->data > num2->data ? temp2 : temp1;
                break;
            }
            num1 = num1->next;
            num2 = num2->next;
        }
    }
    
    if (lnode == NULL && snode == NULL) 
    {
        return create_new_node(0);
    }

    borrow = 0;
    result = subtract_helper(lnode, snode);
    reverse_list(&result);
    return result;
}

//Multiply
node* make_empty_list(int size)
{
	struct node* head = NULL;
	while (size--)
        insert_at_begining(&head, 0);
	return head;
}

node* multiply_Two_Lists(node** first_ref, node** second_ref)
{
    int m = findLength(*first_ref);
    int n = findLength(*second_ref);

	node* result = make_empty_list(m + n + 1);

	node* second_ptr = (*second_ref);
    node* result_ptr1 = result;
    node* result_ptr2 = NULL;
    node* first_ptr = NULL;

	// multiply each node of second list with first
	while (second_ptr) 
    {
		int carry = 0;
		// each time we start from the next of node from which we started last time
		result_ptr2 = result_ptr1;
		first_ptr = (*first_ref);

		while (first_ptr) 
        {
			// multiply a first list's digit with a current second list's digit
			int mul = first_ptr->data * second_ptr->data + carry;

			result_ptr2->data += mul % 10;

			// now resultant node itself can have more than 1 digit
			carry = mul / 10 + result_ptr2->data / 10;
			result_ptr2->data = result_ptr2->data % 10;

			first_ptr = first_ptr->next;
			result_ptr2 = result_ptr2->next;
		}

		// if carry is remaining from last multiplication
		if (carry > 0) 
        {
			result_ptr2->data += carry;
		}

		result_ptr1 = result_ptr1->next;
		second_ptr = second_ptr->next;
	}

	// reverse the result_list as it was populated from last node
	reverse_list(&result);

	// remove if there are zeros at starting
	while (result->data == 0) 
    {
		struct node* temp = result;
		result = result->next;
		free(temp);
	}
    reverse_list(&result);
	return result;
}

//Divide
int compare_LL(node* first, node* second)  //compares 2 numbers stored as LL and returns the larger one
{
    node* p1 = first;
    node* p2 = second;
    if(findLength(first) == findLength(second))
    {
        while(p2->next!=NULL)
        {
            if(p1->data > p2->data)
            {
                return 1;
            }
            else if(p1->data < p2->data)
            {
                return 2;
            }
            else
            {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    else if(findLength(first) > findLength(second))
    {
       return 1;
    }
    else if(findLength(first) < findLength(second))
    {
        return 2;
    }
    return 1;
}

node* copy_LL(node* head)
{
    node* result = NULL;
    node* ptr = head;
    while(ptr!=NULL)
    {
        insert_at_begining(&result,ptr->data);
        ptr = ptr->next;
    }
    return result;
}

node* divide_Two_lists(node** first_ref,node** second_ref)
{
    node* first = (*second_ref);
    node* second = (*first_ref);
    node* result = NULL;
    node* one = NULL;
    insert_at_begining(&one,1);

    reverse_list(&first);
    reverse_list(&second);
    node* second_copy = copy_LL(second);
    int greater = compare_LL(first,second);
    reverse_list(&first);
    reverse_list(&second);

    if(greater == 2)
    {
        result = make_empty_list(1);
    }
    else if(greater == 1)
    {
        int large = 1;
        while(large == 1)
        {
            second = add_Two_Lists(&second,&second_copy);
            result = add_Two_Lists(&result,&one);

            reverse_list(&first);
            reverse_list(&second);
            large = compare_LL(first,second);
            reverse_list(&first);
            reverse_list(&second);
        }
    }
    return result;
}
