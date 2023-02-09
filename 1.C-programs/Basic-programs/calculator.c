#include <stdio.h>
#include <stdlib.h>
/*This is a calculator program using functions*/

//The functions of add,sub,multiply and divide are defined below
float add(float x,float y)
{
    float addition = x + y;
    return (addition);
}

float sub(float x,float y)
{
    float subtraction = x - y;
    return (subtraction);
}

float multiply(float x,float y)
{
    float multiplication = x * y;
    return (multiplication);
}

float divide(float x,float y)
{
    float division = x / y;
    return (division);
}

//the main function starts from here

int main()
{
   float num1,num2;
   float a,s,m,d;

//receiving input from user

   printf("\nEnter first number:");
   scanf("%f",&num1);
   printf("\nEnter second number:");
   scanf("%f",&num2);

//functions are invoked below

   a = add(num1,num2);
   s = sub(num1,num2);
   m = multiply(num1,num2);
   d = divide(num1,num2);

//Output

   printf("\nThe addition of these numbers is:%.2f\n",a);
   printf("The subtraction of these numbers is:%.2f\n",s);
   printf("The multiplication of these numbers is:%.2f\n",m);
   printf("The division of these numbers is:%f\n",d);

    return 0;
}
