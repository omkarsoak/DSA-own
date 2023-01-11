/*
TAKES A STRING AS INPUT AND CHECKS IF PARANTHESES ARE MATCHING
USING STACK
IF WE GET (,{,[ THEY ARE PUSED INTO STACK 
AND IF WE GET ),},] THEN ITEM IS POPPED FROM THE STACK
ALL OTHER CHARACTERS ARE IGNORED
*/

#include <stdio.h>
#include <stdlib.h>
struct stack
{
    int size;
    int top;
    char* arr;
};

int is_empty(struct stack *ptr)
{
    if(ptr->top==-1)
    {return 1;}
    else
    {return 0;}
}

int is_full(struct stack *ptr)
{
    if(ptr->top==(ptr->size-1))
    {return 1;}
    else
    {return 0;}
}

void push(struct stack *ptr,char data)
{
    if(is_full(ptr)==1)
    {printf("Stack overflow\n");}
    else
    {
        ptr->top++;
        ptr->arr[ptr->top]=data;
    }
    
}

char pop(struct stack *ptr)
{
    if(is_empty(ptr)==1)
    {
        printf("Stack underflow\n");
        return -1;
    }
    else
    {
        char data = ptr->arr[ptr->top];
        ptr->top--;
        return data;
    }
}

int match(char a,char b)
{
    if(a=='(' && b==')')
    {return 1;}
    else if(a=='[' && b==']')
    {return 1;}
    else if(a=='{' && b=='}')
    {return 1;}
    else
    {return 0;}
}

int parenthesis_matching(char *exp)
{
    struct stack *sp;
    sp->top = -1;
    sp->size = 100;
    sp->arr = (char*)malloc(sizeof(char)*sp->size);
    char popped_char;
    for(int i=0;exp[i]!='\0';i++)
    {
        if(exp[i]=='('||exp[i]=='['||exp[i]=='{')
        {
            push(sp,exp[i]);
        }

        else if(exp[i]==')'||exp[i]==']'||exp[i]=='}')
        {
            if(is_empty(sp)==1)
            {return 0;}
            popped_char = pop(sp);
            if(match(popped_char,exp[i])!=1)
            {return 0;}
        }
    }
    if(is_empty(sp)==1)
    {return 1;}
    else
    {return 0;}
}

int main()
{
    char *arr = (char*)malloc(sizeof(char)*100);
    printf("Enter the expression: ");
    scanf("%s",arr);
    printf("Entered string is: %s\n",arr);
    int ans = parenthesis_matching(arr);
    if(ans==1)
    {printf("Paranthesis are matching\n");}
    else
    {printf("Paranthesis are not mathcing\n");}

    return 0;
}
