/************************************
THIS PROGRAM USES MALLOC() FUNCTION
IT OUTPUTS THE STRING THAT WE INPUTED
*************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    char *text = NULL;
    printf("Enter a the limit of the text:");
    scanf("%d",&size);

    //DYNAMIC MEMORY IS ALLOCATED
    text = (char *)malloc(size * sizeof(char));

    //This if statement is used to check that the pointer is not already used

    if(text != NULL)            //This if statement is not necessary
    {
        printf("Enter a string:");
        scanf("%s",text);

        printf("inputted text is:%s",text);
    }

    free(text);        //freeing memory after use id important
    text = NULL;

    return 0;
}
