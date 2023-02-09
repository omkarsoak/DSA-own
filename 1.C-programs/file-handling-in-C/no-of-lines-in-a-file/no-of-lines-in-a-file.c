/*****************************
THIS PROGRAM COUNTS
THE NUMBER OF LINES IN A FILE
******************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *pfile = NULL;
    pfile = fopen("myfile4.txt","r");
    char letter;
    int lines_count = 0;

    //THIS CHECKS IF THE POINTER IS NULL
    //IF THE POINTER IS NULL THAT MEANS THAT THE FILE DOES NOT EXIST
    if (pfile == NULL)
    {
        printf("File not found");
    }

    //WHILE LOOP TO COUNT CHARACTERS TILL EOF
    while((letter = fgetc(pfile)) != EOF)
    {
        if(letter == '\n')    //COUNTS THE NUMBER OF LINES
        {
            lines_count++;
        }
    }

    fclose(pfile);

    printf("Total number of lines are:%d\n",++lines_count);
    //lines_count IS INCREMENTED AS LAST LINE IS NOT COUNTED BY THE PROGRAM
    //AS EOF COMES BEFORE \n

    return 0;
}
