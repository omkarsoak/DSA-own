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
#include <string.h>
#include <ctype.h>
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

int reverse_list(node** head_ref)
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
    return result;
}

//Subtract
int findLength(node* ptr)
{
    int size = 0;
    while (ptr != NULL) 
    {
        ptr = ptr->next;
        size++;
    }
    return size;
}

node* paddZeros(node* snode, int diff)
{
    if (snode == NULL)
        return NULL;
    
    while (diff!=0) 
    {
        insert_at_end(&snode,0);
        diff--;
    }
    return snode;
}

static int borrow;
node* subtract_helper(node* l1,node* l2)
{
    if (l1 == NULL && l2 == NULL && borrow == 0)
        return NULL;
  
    node* previous = subtract_helper(
        l1 ? l1->next : NULL, l2 ? l2->next : NULL);
  
    int d1 = l1->data;
    int d2 = l2->data;
    int sub = 0;
  
    /* if you have given the value to next digit then
       reduce the d1 by 1 */
    if (borrow) {
        d1--;
        borrow = 0;
    }
  
    /* If d1 < d2, then borrow the number from previous
       digit. Add 10 to d1 and set borrow = true; */
    if (d1 < d2) {
        borrow = 1;
        d1 = d1 + 10;
    }
  
    /* subtract the digits */
    sub = d1 - d2;
  
    /* Create a node with sub value */
    node* current = create_new_node(sub);
  
    /* Set the Next pointer as Previous */
    current->next = previous;
  
    return current;
}

node* subtract_Two_Lists(node** first_ref,node** second_ref)
{
    node* num1 = (*first_ref);
    node* num2 = (*second_ref);
    node* result;

    node *lnode = NULL, *snode = NULL;
    
    node* temp1 = num1;
    node* temp2 = num2;

    int num1Length = findLength(num1);
    int num2Length = findLength(num2);

    if(num1Length!=num2Length)
    {
        lnode = num1Length > num2Length ? num1 : num2;
        snode = num1Length > num2Length ? num2 : num1;
        snode = paddZeros(snode, abs(num1Length - num2Length));
    }
    else
    {
        while (num1 && num2) 
        {
            if (num1->data != num2->data) {
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
	// reverse the lists to multiply from end
	// m and n lengths of linked lists to make
	// and empty list
	int m = reverse_list(first_ref);
    int n = reverse_list(second_ref);

	node* result = make_empty_list(m + n + 1);

	// pointers for traverse linked lists and also
	// to reverse them after
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
			// multiply a first list's digit with a
			// current second list's digit
			int mul = first_ptr->data * second_ptr->data + carry;

			result_ptr2->data += mul % 10;

			// now resultant node itself can have more
			// than 1 digit
			carry = mul / 10 + result_ptr2->data / 10;
			result_ptr2->data = result_ptr2->data % 10;

			first_ptr = first_ptr->next;
			result_ptr2 = result_ptr2->next;
		}

		// if carry is remaining from last multiplication
		if (carry > 0) {
			result_ptr2->data += carry;
		}

		result_ptr1 = result_ptr1->next;
		second_ptr = second_ptr->next;
	}

	// reverse the result_list as it was populated
	// from last node
	reverse_list(&result);
	reverse_list(first_ref);
	reverse_list(second_ref);

	// remove if there are zeros at starting
	while (result->data == 0) {
		struct node* temp = result;
		result = result->next;
		free(temp);
	}
	return result;
}

//Divide

int compare_LL(node* first, node* second)
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

void remove_padding(node** head_ref)
{
    node* ptr = (*head_ref);
    int count = 0;
    while(ptr->next!=NULL)
    {
        if(ptr->data == 0)
        {
            count++;
        }
        ptr = ptr->next;
    }
    if(count == 0)
    {
        return;
    }
    for(int i=0;i<=count;i++)
    {
        delete_node_atValue(head_ref,0);
    }
}

node* divide_Two_lists(node** first_ref,node** second_ref)
{
    int size1 = reverse_list(first_ref);
    int size2 = reverse_list(second_ref);
    node* first = (*first_ref);
    node* second = (*second_ref);
    node* second_copy = copy_LL(second);
    node* result = NULL;
    node* one = NULL;
    insert_at_begining(&one,1);
    int greater = compare_LL(first,second);\
    if(greater == 2)
    {
        result = make_empty_list(1);
    }
    else if(greater == 1)
    {
        int large = 1;
        while(large == 1)
        {
            first = subtract_Two_Lists(&first,&second_copy);

            remove_padding(&second_copy);
         
            result = add_Two_Lists(&result,&one);
           
            large = compare_LL(first,second_copy);
        }
    }
    return result;
}


//stack
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

char* infix_to_postfix(char* infix)
{
    stack* sp = (stack*)malloc(sizeof(stack));
    stack_initialize(sp,100);

    char* postfix = (char*)malloc((strlen(infix)+1) * sizeof(char));
    int i = 0; // Track infix traversal
    int j = 0; // Track postfix addition 
    
    while (infix[i]!='\0')
    {
        if (infix[i] == '(')
        {
            push(sp,infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while((peek(*sp))!='(')
            {
                postfix[j] = pop(sp);
                j++;
            }
            pop(sp);
            i++;
        }
        if(is_operand(infix[i]))
        {
            do{
                postfix[j] = infix[i];
                j++;
                i++;
            } while(is_operand(infix[i]));
            postfix[j]=' ';
            j++;
        }
        else if(is_operator(infix[i]))
        {
            if(precedence(infix[i]) > precedence(peek(*sp)))
            {
                push(sp, infix[i]);
                i++;
            }
            else
            {
                postfix[j] = pop(sp);
                j++;
            }
        }
        else 
        {
            i++;
        }
    }
    while (!isempty(sp))    
    {
        postfix[j] = pop(sp);
        j++;
    }
    postfix[j] = '\0';
    return postfix;
}

node** convert_to_lists(char input[],int *counter)
{
    int count = 0;
    int x=0;
    for(x=0;input[x]!='\0';x++)
    {
        if(is_operator(input[x]))
        {
            count++;
        }
    }

    //printf("count: %d",count);
    printf("input: %d\n",x);
    printf("done 0");
    node** num_ptr_arr = (node**)malloc(sizeof(node*)*(count+1));
    printf("done1 ");
    for(int i=0;i<count+1;i++)
    {
        printf("done2 ");
        num_ptr_arr[i] = NULL;
    }

    printf("done");

    int i=0;
    for(int x=0;input[x]!='\0';x++)
    {
        if(is_operator(input[x]) == 1 || input[x] == ' ')
        {
            if(is_operand(input[x+1]))
            {
                i++;
            }
        }
        else if(is_operand(input[x]))
        {
            insert_at_begining(&num_ptr_arr[i],input[x]-'0');
        }
    }
    *counter = count;
    return num_ptr_arr;
}

typedef struct Stack
{
    int size;
    int top;
    node** arr;
}Stack;

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

//stack operations for node stack
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


node* evaluate_postfix(node** arr,char postfix[])
{
    Stack s1;
    int i=0;
    int num_count = 0;
    while(i < strlen(postfix))
    {
        int data = postfix[i];
        if(is_operand(postfix[i]))
        {
            Push(&s1,arr[num_count]);
            num_count++;
            while (is_operand(postfix[i]))
            {
                i++;
            }
        }
        if(is_operator(postfix[i]))
        {
            node* second_op = Pop(&s1);
            node* first_op = Pop(&s1);
            node* temp = NULL;
            switch(postfix[i])
            {
                case('+'):
                    temp = add_Two_Lists(&first_op,&second_op);
                    break;
                case('-'):
                    temp = subtract_Two_Lists(&first_op,&second_op);
                    break;
                case('*'):
                    temp = multiply_Two_Lists(&first_op,&second_op);
                    break;
                case('/'):
                    temp = divide_Two_lists(&first_op,&second_op);
                    break;
                default:
                    break;
            }
            Push(&s1,temp);
            i++;
        }
        else
        {
            i++;
        }
    }
}

int main()
{
    node* head1 = NULL;
    node* head2 = NULL;
    node* result;
    printf("Enter the calculation:\n");
    char infix[100];
    //scanf("%s",infix);

    strcpy(infix,"203948768768768768678209834092384-23897982479284+29892489834934");
    char *postfix;
    postfix = infix_to_postfix(infix);
    for(int x=0;postfix[x]!='\0';x++)
    {
        printf("%c", postfix[x]);
    }

    printf("\n");
    int length = 0;  //number of numbers (i.e num of LL created from postfix)
    node** arr = convert_to_lists(postfix,&length);
    for(int j=0;j<=length;j++)
    {
        printf("Num %d: ",j);
        traverse_list(arr[j]);
        printf("\n");
    }

    //traverse_list(arr[0]);
    //traverse_list(arr[1]);

    //result = add_Two_Lists(&arr[0],&arr[1]);
    //traverse_list(result);

    //insert_at_begining(&head1,1);
    //insert_at_begining(&head1,8);
    //insert_at_begining(&head1,2);
    //insert_at_begining(&head1,8);
    //insert_at_begining(&head1,5);
    

    //insert_at_begining(&head2,4);
    //insert_at_begining(&head2,2);
    //insert_at_begining(&head2,1);
    //insert_at_begining(&head2,1);
    //insert_at_begining(&head2,2);

    //traverse_list(head1);
    //traverse_list(head2);
    //node* ans = divide_Two_lists(&head1,&head2);
    //traverse_list(head1);
    //traverse_list(head2);
    //node* ans1 = compare_LL(head1,head2);
    //traverse_list(ans);


    return 0;
}
