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
#include "linked_list.h"
#include "stack.h"
#include "operations.h"

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