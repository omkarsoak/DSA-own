/*******************************
THIS PROGRAM HAS TWO FUNCTIONS -
1.) REVERSING ORDER OF STRING
2.) BUBBLE SORTING OF STRINGS
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaring functions

void bubbleSort(char string[10][20], int num);
void reverseString(char str[],int str_length);

/*************
 MAIN FUNCTION
**************/

int main()
{
    //Reversing order of string

    char string1[100];
    int length;

    printf("\nPrint individual characters of string in reverse order\n\n");
    printf("Enter the string:");
    scanf("%s",string1);

    length = strlen(string1);

    printf("\nthe characters in the string in reverse are: \n");

    reverseString(string1,length);

    printf("\n---------------------------------------------------------\n");

    //Bubble sorting of strings

    printf("Bubble sort\n");

    char string2[10][20];
    int num,count1,count2;

    //Taking input

    printf("Enter the number of strings to be sorted:");
    scanf("%d",&num);

    printf("\nInput the strings to be sorted:\n");

    for (count1 = 0; count1 < num; count1++)
    {
        scanf("%s",string2[count1]);
    }

    printf("\n---------------------------------------------------------\n");

    //bubbleSort() Function called

    bubbleSort(string2,num);

    //Giving output

    printf("\nStrings in sorted order are:\n");

    for (count2 = 0; count2 < num ; count2++)
    {
       printf("%s\n",string2[count2]);
    }

    printf("\n---------------------------------------------------------\n");

    return 0;
}

/**********************
REVERSE STRING FUNCTION
***********************/

void reverseString(char str[],int str_length)
{
    int i;

    for (i = str_length; i>=0; i--)
    {
        printf("%c",str[i]);
    }
}

/*******************
BUBBLE SORT FUNCTION
********************/

void bubbleSort(char string[10][20], int num)
{
    int i,j;
    char temp[20];
    for (i = 0;i < num - 1; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if(strcmp(string[i],string[j]) > 0)
            {
                strcpy(temp, string[i]);
                strcpy(string[i], string[j]);
                strcpy(string[j], temp);
            }
        }
    }

}
