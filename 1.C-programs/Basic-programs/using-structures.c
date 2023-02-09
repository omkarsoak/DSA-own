/**************************************
THIS PROGRAM USES STRUCTURES TO
INPUT EMPLOYEE DATA AND THEN OUTPUT IT
***************************************/
#include <stdio.h>
#include <stdlib.h>

/*NESTED STRUCTURES : THE STRUCTURE "hire_date" IS USED INSIDE STRUCTURE "employee"*/
struct hire_date
    {
        int day;
        int month;
        int year;
    };

//STRUCTURE EMPLOYEE
struct employee
{
    char name[20];
    struct hire_date date;  //A VARIABLE date IS DECLARED OF STRUCTURE hire_date
    float salary;
};

int main()
{
    struct employee employee_1;     //A VARIABLE employee_1 IS DECLARED OF STRUCTURE employee

    /*TAKING INPUT FROM THE USER*/
    printf("\nEnter employee details:\n");
    printf("Enter name:");
    scanf("%s",employee_1.name);
    printf("\nEnter the hiring date:\n");
    printf("day:");
    scanf("%d",&employee_1.date.day);
    printf("month:");
    scanf("%d",&employee_1.date.month);
    printf("year:");
    scanf("%d",&employee_1.date.year);
    printf("\nEnter the salary:");
    scanf("%f",&employee_1.salary);

    printf("\n---------------------------------------------------\n");

    /*GIVING OUTPUT*/
    printf("Employee details\n");
    printf("Employee name:%s\n",employee_1.name);
    printf("Employee hiring date is:%d/%d/%d\n",employee_1.date.day,employee_1.date.month,employee_1.date.year);
    printf("Employee salary:%.2f\n",employee_1.salary);

    return 0;
}
