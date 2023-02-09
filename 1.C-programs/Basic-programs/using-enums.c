#include <stdio.h>
int main()
{
    //the indentifiers are specified and yahoo is assigned a value
    enum company {GOOGLE,FACEBOOK,XEROX,YAHOO=20,EBAY};

   //here we are assigning enum identifier to the variable

    enum company var1= GOOGLE,var2 = XEROX,var3 = EBAY;

    printf("the integer of google is: %d\n",var1);
    printf("the integer of xerox is: %d\n",var2);
    printf("the integer of ebay is: %d\n",var3);
    return 0;
    /*so in output we get
    google is 0
    xerox is 2
    ebay is 21*/
}
