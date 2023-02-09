/*****************************
THIS PROGRAM READS FROM A FILE
AND THEN DISPLAYS IT
******************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *pfile = NULL;
    pfile = fopen("myfile3.txt","r");

    //THIS CHECKS IF THE POINTER IS NULL
    //IF THE POINTER IS NULL THAT MEANS THAT THE FILE DOES NOT EXIST
    if (pfile == NULL)
    {
        printf("File not found");
    }

    char str[61];

    //FILE IS READ
    while(fgets(str,60,pfile) != NULL)
    {
        printf("%s",str);   //CONTENTS OF FILE PRINTED
    }

    fclose(pfile);  //FILE IS CLOSED

    return 0;
}
