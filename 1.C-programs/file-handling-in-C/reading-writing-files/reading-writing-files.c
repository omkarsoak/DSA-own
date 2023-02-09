/*****************************************************
THIS PROGRAM HAS TWO SECTIONS
SECTION 1: WRITES HARD CODED DATA TO A FILE
SECTION 2: ACCEPTS DATA FROM USER AND WRITES TO A FILE
******************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    /******** SECTION 1 *********/

    //FILE myfile1.txt IS CREATED
    FILE *pfile1;
    pfile1 = fopen("myfile1.txt","w+");

    //THIS CHECKS IF THE POINTER IS NULL
    //IF THE POINTER IS NULL THAT MEANS THAT THE FILE DOES NOT EXIST
    if (pfile1 == NULL)
    {
        printf("File not found");
    }

    char str1[] = "in the 18th century,";
    char str2[] = "the city was the seat of the Peshwas";

    //USING fprintf() FOR WRITING FORMATTED DATA
    fprintf(pfile1,"%s\n%s\n",str1,str2);

    //USING fputs() FOR WRITING STRINGS
    fputs("My name is omkar oak",pfile1);

    fclose(pfile1);  //CLOSING THE FILE

    printf("Data is written to file myfile1.txt\n");

    printf("\n--------------------------------------------------------\n");

    /******** SECTION 2 *********/

    //FILE myfile2.txt IS CREATED
    FILE *pfile2;
    pfile2 = fopen("myfile2.txt","w+");

    //THIS CHECKS IF THE POINTER IS NULL
    //IF THE POINTER IS NULL THAT MEANS THAT THE FILE DOES NOT EXIST
    if (pfile2 == NULL)
    {
        printf("File not found");
    }

    int i;
    char data[100];

    printf("Enter data to be written to another file\n");


    //THIS FOR LOOP ACCEPTS DATA FROM USER
    for(i=1;i<=5;i++)
    {
        printf("Enter data for line %d:",i);
        scanf("%s",data);
        fprintf(pfile2,"%s\n",data);    //DATA PRINTED TO THE FILE
    }

    fclose(pfile2);  //FILE IS CLOSED

    //GENERAL INFORMATION PRINTED
    printf("\n--------------------------------------------------------\n");
    printf("Data stored in myfile2.txt\n");
    printf("Path of file: D:\\Omkar files\\C programs\\reading-writing-files\\myfile2.txt\n");
    printf("\n--------------------------------------------------------\n");
    return 0;
}
