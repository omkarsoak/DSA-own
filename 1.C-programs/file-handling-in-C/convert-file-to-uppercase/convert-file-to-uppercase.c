/************************************************************************
THIS PORGRAM CONVERTS A FILE TO UPPERCASE
IT HAS FOUR SECTIONS -
SECTION 1: READS A FILE
SECTION 2: CONVERTS ALL CHARACTERS TO UPPERCASE
SECTION 3: WRITES THE UPPERCASED DATA TO ANOTHER FILE
SECTION 4: PRINTS ALL UPPERCASED DATA ON TERMINAL (TO CONFIRM THE TRANSFER)
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    //THIS HEADER FILE CONTAINS islower() function

int main()
{
    FILE *pfile1 = NULL;         //ORGINAL FILE
    FILE *ptemp_file = NULL;    //TEMPORARY FILE
    FILE *pfile2 = NULL;       //UPPERCASED DATA CONTAINING FILE

    //ORIGINAL & TEMP FILE OPENED
    pfile1 = fopen("myfile5.txt","r");
    ptemp_file = fopen("tempfile.txt","w+");

    //CHECKING IF FILES EXISTS
    if(pfile1 == NULL)
    {
        printf("file not found");
    }

    if(ptemp_file == NULL)
    {
        printf("temporary file not found");
    }

    /********************SECTION 1 & 2**********************/

    char letter;

    while((letter = fgetc(pfile1)) != EOF)   //CHECKS FOR EOF(END OF FILE)
    {
        if(islower(letter))   //CHECKS FOR LOWERCASE
        {
            letter = letter -32;  //SYNTAX TO CONVERT LOWERCASE TO UPPERCASE(USING ASCII)
        }

        /******SECTION 3*****/

        fputc(letter, ptemp_file);  //UPPERCASED DATA ENTERED IN TEMPORARY FILE
    }

    //FILES CLOSED
    fclose(pfile1);
    fclose(ptemp_file);

    //TEMP FILE RENAMED
    rename("tempfile.txt","myfile6.txt");

    /**************************SECTION 4***************************/

    pfile2 = fopen("myfile6.txt","r");

    //CHECKING IF FILES EXISTS
    if(pfile2 == NULL)
    {
        printf("file not found");
    }

    //PRINTING DATA TO TERMINAL
    while((letter = fgetc(pfile2)) != EOF)
    {
        printf("%c",letter);
    }

    fclose(pfile2); //FILE CLOSED

    //ALL FILE POINTERS ASSIGNED TO NULL
    pfile1 = NULL;
    pfile2 = NULL;
    ptemp_file = NULL;

    return 0;
}
