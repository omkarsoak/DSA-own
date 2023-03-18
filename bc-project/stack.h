//#include "linked_list.h"
/********CHAR STACK DEFINITION & FUNCTIONS*******/
typedef struct stack
{
    int size;
    int top;
    char* arr;
}stack;

//stack operations
void stack_initialize(stack *s,int size);
int isempty(stack *ptr);
int isfull(stack *ptr);
void push(stack *ptr,char data);
char pop(stack *ptr);
char peek(stack ptr);

/*****NODE STACK DEFINTION & FUNCTIONS*******/
typedef struct Stack
{
    int size;
    int top;
    node** arr;
}Stack;

//stack operations for node stack
void Stack_initialize(Stack *s,int size);
int isEmpty(Stack *ptr);
int isFull(Stack *ptr);
void Push(Stack *ptr,node* root);
node* Pop(Stack *ptr);
node* Peek(Stack ptr);