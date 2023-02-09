/*************************************************
THIS PROGRAM ACCEPTS ITEM DETAILS AND OUTPUTS THEM
USING STRUCTURES POINTERS AND FUNCTIONS
**************************************************/
#include <stdio.h>
#include <stdlib.h>

//THE STRUCTURE item IS DECLARED
struct item
{
    char *item_name;  //the item name is stored as a pointer
    int quantity;
    float price;
    float amount;
};

//Functions are declared
void read_item(struct item *pitem);
void print_item(struct item *pitem);

int main()
{
    struct item item1;
    struct item *pitem;         //POINTER DEFINED
    pitem = &item1;            //POINTER ASSIGNED TO STRUCTURE

    //dynamic memory allocated to item_name
    pitem->item_name = (char*)malloc(30 * sizeof(char));

    //FUNCTIONS ARE CALLED
    read_item(pitem);
    print_item(pitem);

    //Memory is freed
    free(pitem->item_name);

    return 0;
}

/*THIS FUNCTION READS THE DATA FROM THE USER*/
void read_item(struct item *pitem)
{
    printf("\nEnter the product name:");
    gets(pitem->item_name);
    printf("\nEnter the quantity:");
    scanf("%d",&pitem->quantity);
    printf("\nEnter the price:");
    scanf("%f",&pitem->price);
    pitem->amount = pitem->quantity * pitem->price;    //AMOUNT IS CALCULATED
}

/*THIS FUNCTION DISPLAYS ALL THE DATA*/
void print_item(struct item *pitem)
{
    printf("\n------------------------------------------------\n");
    printf("The product details are:\n");
    printf("Name: %s\n",pitem->item_name);
    printf("Quantity: %d\n",pitem->quantity);
    printf("Price: %.2f\n",pitem->price);
    printf("Total amount: %.2f\n",pitem->amount);
}
