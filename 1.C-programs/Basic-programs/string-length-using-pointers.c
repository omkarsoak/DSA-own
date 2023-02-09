/*******************************
THIS PROGRAM CALCULATES
THE STRING LENGTH USING POINTERS
********************************/
#include <stdio.h>
#include <stdlib.h>

//function declaration
int stringLength(char *pstr);

//MAIN FUNCTION
int main()
{
    char string1[20];
    printf("Enter a string:");
    scanf("%s",string1);
    printf("\nthe length of the string is:%d",stringLength(string1));
    return 0;
}

//STRING LENGTH FUNCTION
int stringLength(char *pstring)
{
    char *pstring_end = pstring;
    int str_length;
    while (*pstring_end != '\0')
    {
        pstring_end++;
    }
    str_length = pstring_end - pstring;     //Subtracting two pointers is allowed
    return str_length;
}
