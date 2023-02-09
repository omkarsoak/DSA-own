/*************************************************
THIS PROGRAM REVERSES THE ORDER OF THE CHARACTERS
IN THE FILE AND THEN PRINTS IT OUT
**************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *pfile = NULL;
    pfile = fopen("myfile7.txt","r");    //FILE OPENDED
    int count = 0,i = 1;


    //SETS POSITION TO THE END OF THE FILE
    fseek(pfile,0,SEEK_END);
    count = ftell(pfile);    //THE POSITION IS STORED IN count

    printf("Number of characters: %d\n",count);  //THIS IS JUST TO CONFIRM
    printf("the file in reverse order is:\n");
    printf("\n------------------------------------------\n");

    //THIS LOOP PRINTS OUT THE LAST LETTER OF THE FILE FIRST IN THE TERMINAL
    while(i <= count)
    {
        fseek(pfile,-i,SEEK_END);
        printf("%c",fgetc(pfile));   //PRINTING TO TERMINAL
        i++;
    }

    fclose(pfile);  //FILE CLOSED
    pfile = NULL;   //FILE POINTER SET TO NULL

    printf("\n------------------------------------------\n");

    return 0;
}
