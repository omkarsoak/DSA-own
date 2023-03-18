/*****************
LINUX UTILITY 'bc':
An arbitrary precision calculator which can compute arbitrary length of expression
Input: On the command line
INPUT: STRING OF NUMBERS AND '+ - * /' IN BETWEEN 
OUPUT: ANSWER 
EXAMPLE:
198237918479+83634875862-123312*242
Answer: 2  8  1  8  4  2  9  5  2  8  3  7

DATA STRUCTURES USED:
- LINKED LIST (to store each number with each digit as a node in the LL)
- NODE STACK (stores the numbers as pointer to head node of LL during infix evaluation)
- char STACK (stores operators during infix evaluation)

FUNCTIONS:
- All LL functions
- All Stack functions (one each for node* stack and char stack)
- Add Two Linked Lists
- Subtract Two Linked Lists
- Multiply Two Linked Lists
- Divide Two Linked Lists
- Compare 2 LL (to find greater list)
- Evaluate infix (directly without needing to convert to postfix - using 2 stack)
****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


/********CHAR STACK DEFINITION & FUNCTIONS*******/
typedef struct stack
{
    int size;
    int top;
    char* arr;
}stack;

//stack operations
void stack_initialize(stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->arr = (char*)malloc(s->size*sizeof(char));
}

int isempty(stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int isfull(stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;} 
}

void push(stack *ptr,char data)
{
    if(isfull(ptr)==1)  //stack overflow
    {return;}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = data;
    }
}

char pop(stack *ptr)
{
    if(isempty(ptr)==1)  //stack underflow
    {return -1;}
    else
    {
        char data = ptr->arr[ptr->top];
        ptr->top--;
        return data;
    }
}

char peek(stack ptr)   //returns top value
{
    if(isempty(&ptr))
    {return -1;}
    else
    {return ptr.arr[ptr.top];}   
}

/*****NODE STACK DEFINTION & FUNCTIONS*******/
typedef struct Stack
{
    int size;
    int top;
    node** arr;
}Stack;

//stack operations for node stack
void Stack_initialize(Stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->arr = (node**)malloc(s->size*sizeof(node*));
}

int isEmpty(Stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int isFull(Stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;} 
}

void Push(Stack *ptr,node* root)
{
    if(isFull(ptr)==1)  //stack overflow
    {return;}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = root;
    }
}

node* Pop(Stack *ptr)
{
    if(isEmpty(ptr)==1)  //stack underflow
    {return NULL;}
    else
    {
        node* head = ptr->arr[ptr->top];
        ptr->arr[ptr->top] = NULL;
        ptr->top--;
        return head;
    }
}

node* Peek(Stack ptr)   //returns top value
{
    if(isEmpty(&ptr))
    {return NULL;}
    else
    {return ptr.arr[ptr.top];}   
}

/*****EVALUATE EXPRESSION******/
//AUXILLARY FUNCTIONS
int precedence(char symbol)  //assign precendence to operator
{
	if(symbol == '^')   //exponent operator, highest precedence
	{return 3;}
	else if(symbol == '*' || symbol == '/')
	{return 2;}
	else if(symbol == '+' || symbol == '-')         //lowest precedence
	{return 1;}
	else
	{return 0;}
}

int is_operator(char symbol)   
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{return 1;}
	else
	{return 0;}
}

int is_operand(char ch)
{
    return ('0'<=ch && ch<='9');
}

node* operation(node* val1,node* val2,char ops)
{
    node* temp = NULL;
    switch(ops)
    {
        case('+'):
            temp = add_Two_Lists(&val1,&val2);
            break;
        case('-'):
            temp = subtract_Two_Lists(&val1,&val2);
            break;
        case('*'):
            temp = multiply_Two_Lists(&val1,&val2);
            break;
        case('/'):
            temp = divide_Two_lists(&val1,&val2);
            break;
        default:
            break;
    }
    return temp;
}

//EVALUATE EXPRESSION
node* evaluate_infix(char infix[])
{
    int count = 0;
    int x=0;
    for(x=0;infix[x]!='\0';x++)
    {
        if(is_operator(infix[x]))
        {
            count++;
        }
    }

    node** num_ptr_arr = (node**)malloc(sizeof(node*)*(count+1));
    for(int i=0;i<count+1;i++)
    {
        num_ptr_arr[i] = NULL;
    }

    Stack* s1 = (Stack*)malloc(sizeof(Stack)*(count+1));  //node stack
    Stack_initialize(s1,100);
    stack* s2 = (stack*)malloc(sizeof(stack));  //operator stack
    stack_initialize(s2,100);

    int i=0;
    int j=0;

    while(infix[i]!='\0')
    {
        //brackets functionality remaining
        /*if (infix[i] == '(')
        {
            push(s2,infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while((peek(*s2))!='(')
            {
                postfix[j] = pop(s2);
                j++;
            }
            pop(sp);
            i++;
        }*/
        if(is_operand(infix[i]))
        {
            do
            {
                insert_at_begining(&num_ptr_arr[j],infix[i]-'0');
                i++;
            } while(is_operand(infix[i]));
            Push(s1,num_ptr_arr[j]);
            j++;
        }
        else if(is_operator(infix[i]))
        {
            if(isempty(s2) == 1)
            {
                push(s2, infix[i]);
                i++;
            }
            else
            {
                while(isempty(s2)!=1 && precedence(infix[i]) <= precedence(peek(*s2)))
                {
                    char ops = pop(s2);
                    node* val1 = Pop(s1);
                    node* val2 = Pop(s1);
                    node* res = operation(val1,val2,ops);
                    Push(s1,res);
                }
                push(s2,infix[i]);
                i++;
            }
        }
        else 
        {
            i++;
        }
    }
    while(isempty(s2)!=1)
    {
        char ops = pop(s2);
        node* val1 = Pop(s1);
        node* val2 = Pop(s1);
        node* res = operation(val1,val2,ops);
        Push(s1,res);
    }
    return Pop(s1);
}

int main()
{
    node* result;
    printf("Enter the calculation:\n");
    char infix[200];
    scanf("%s",infix);
    
    result = evaluate_infix(infix);
    reverse_list(&result);
    traverse_list(result);

    return 0;
}

//norm: require: ulti list, return: ulti list
