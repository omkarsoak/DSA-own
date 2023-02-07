/***********
CONVERTS INFIX TO POSTFIX AND THEN EVALUATES THE EQUATION
INPUT:
1. INFIX EXPRESSION AS STRING
OUTPUT:
1. POSTFIX EXPRESSION AS LINKED LIST
2. ANSWER AFTER EVALUATING POSTFIX EXPRESSION
METHOD:
1. CONVERT INPUT STRING TO LINKED LIST (INFIX)
2. CONVERT (INFIX LINKED LIST) TO (POSTFIX LINKED LIST)
3. EVALUATE POSTFIX LINKED LIST EXPRESSION
USED:
1. 2 LINKED LIST (INFIX & POSTFIX)
2. 2 STACK (DURING CONVERSION & DURING EVALUATION)
NOTE: 
THE STACK IS MADE USING LIKED LIST 
************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    char data;   //NOTE: USED char INSTEAD of int
    struct node *next;
}node;
//Thus everywhere further use 'char'

typedef node* stack;

/*************Linked list functions*************/
void linked_list_traversal(node* ptr)
{
    while(ptr!=NULL)
    {
        printf("%c ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void insert_at_end(node** head_ref,char data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head_ref == NULL)  
    {
       *head_ref = new_node;
       return;
    } 
    node* p = *head_ref;
    while(p->next!=NULL)  
    {
        p = p->next;
    }
    p->next = new_node;
}

/************Stack functions**************/
int is_empty(node* top)
{
    if(top==NULL)
    {return 1;}
    else
    {return 0;}
}

int is_full(node* top)
{
    node* n = (node*)malloc(sizeof(node));
    if(n==NULL)
    {return 1;}
    else
    {return 0;}
}

void push(node** top,char data)
{
    if(is_full(*top)==1)
    {printf("Stack overflow\n");}
    else
    {
        node* n = (node*)malloc(sizeof(node));
        n->data = data;
        n->next = *top;
        *top = n;
    }
}

char pop(node** top)
{
    if(is_empty(*top)==1)
    {printf("Stack underflow\n");}
    else
    {
        node* top1 = *top;
        char data = top1->data;
        top1 = top1->next;
        free(*top);
        *top = top1;
        return data;
    }
}

char peek(node* top)
{
    node* ptr = top;
    if(ptr!=NULL)
    {
        return ptr->data;
    }
    else 
    {return -1;}
}


/*****infix-postfix auxillary functions****/

int is_operator(char symbol)   
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{return 1;}
	else
	{return 0;}
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

//CONVERTS INFIX TO POSTFIX
void infix_to_postfix(node** infix, node** postfix)  //accepts 2 linked lists
{
    int i=0,j=0;
    char item;
    node* infix_exp = (*infix);
    stack s1;

    item = infix_exp->data;   //item = 1st node's data

    while(infix_exp!=NULL)
    {
        item = infix_exp->data;
        infix_exp = infix_exp->next;

        /*We can encounter only 3 types of things in infix:
            - operand
            - operator
            - bracket = opening or closing
        */

        if(item == '(')   //opening bracket
        {
            //push in stack as it is
            push(&s1,item);
        }

        else if(isdigit(item) || isalpha(item))   //operand
        {
            //write to postfix as it is
            insert_at_end(postfix,item);    
        }

        else if(is_operator(item)==1)   //operator
        {
            //push into stack and pop all higher and equal precedence operators to the answer
            while(is_empty(s1)!=1 && precedence(item)<=precedence(peek(s1)))
            {
                insert_at_end(postfix,pop(&s1));
            }
            push(&s1,item);
        }

        else if(item == ')')   //closing bracket
        {
            //pop everything until opening bracket and ignore opening bracket
            while(is_empty(s1)!=1 && peek(s1)!='(')
            {
                insert_at_end(postfix,pop(&s1));
            }
            pop(&s1);  //popping opening bracket
        }
    }

    //pop everything remaining in the stack into the postfix expression
    while(is_operator(peek(s1)) || peek(s1)=='(' || peek(s1)==')')
    {
        if(is_operator(peek(s1)))
            insert_at_end(postfix,pop(&s1));
        else
            pop(&s1);
    }
}


int evaluate_postfix(node** postfix)   //linked list as postfix
{
    stack s2;
    node* postfix_exp = (*postfix);

    while(postfix_exp!=NULL)
    {
        int item = postfix_exp->data;

        if(isdigit(postfix_exp->data))   //if element is number, push into stack
        {
            push(&s2,(postfix_exp->data-'0'));
        }
        else
        {
            //If the element is an operator, pop operands for the operator from the stack
            int val1 = pop(&s2);
            int val2 = pop(&s2);

            //Evaluate the operator and push the result back to the stack
            switch (postfix_exp->data)
            {
                case '+': push(&s2, val2 + val1); break;
                case '-': push(&s2, val2 - val1); break;
                case '*': push(&s2, val2 * val1); break;
                case '/': push(&s2, val2/val1); break;
            }
        }
        postfix_exp = postfix_exp->next;
    }
    //When the expression is ended, the number in the stack is the final answer
    return pop(&s2);
}

int main()
{
    node* infix = NULL;
    node* postfix = NULL;
    char expr[] = "2+(3*4-(5/6^7)*8)*9";

    //convert input array to linked list
    int n = strlen(expr);
    for(int i=0;i<n;i++)
    {
        insert_at_end(&infix,expr[i]);
    }

    //Output
    printf("Infix: ");
    linked_list_traversal(infix);

    infix_to_postfix(&infix,&postfix);

    printf("Postfix: ");
    linked_list_traversal(postfix);

    //int ans = evaluate_postfix(&postfix);
    //printf("The answer is: %d\n",ans);

    return 0;
}
