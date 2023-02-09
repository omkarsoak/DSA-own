/***************************************************
THIS PROGRAM CONTAINS FUNCTIONS CREATED SIMILAR TO
1.) strlen() function ---- FINDING LENGTH OF A STING
2.) strcat() function ---- CONCATING TWO STRINGS
****************************************************/

#include <stdio.h>
#include <stdlib.h>

// functions are declared

int stringLength(char string[]);
void stringConcat (char result[],char str1[],char str2[]);

//main function

int main()
{
    //FINDING STRING LENGTH

    char input_string[20];
    printf("find out the length of a string\n");
    printf("input a string:");
    scanf("%s",input_string);

    printf("the length of the above string is: %d\n",stringLength(input_string));

    //CONCATING TWO STRINGS

    char string1[20];
    char string2[20];
    char concat[40];
    printf("\nTo concate two strings:\n");

    printf("\ninput first string:");
    scanf("%s",string1);
    printf("\ninput second string:");
    scanf("%s",string2);

    stringConcat(concat,string1,string2);

    printf("The concated string is: %s",concat);

    return 0;
}

/**function similar to strlen() function**/

int stringLength(char string[])
{
    int length;
    for (length=0;string[length] != '\0';length++)
    {
        length++;
    }
    return (length - 1);
}

/**function similar to strcat() function**/

void stringConcat (char result[],char str1[],char str2[])
{
    int i,j;
    for (i = 0; str1[i] != '\0';i++)
    {
        result[i] = str1[i];
    }
    for (j=0; str2[j] != '\0'; j++)
    {
        result[i + j] = str2[j];
    }
}
