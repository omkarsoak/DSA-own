/********
MENU DRIVEN PROGRAM
FOR SEARCHIGN AND SORTING OPERATIONS
********/
#include <stdio.h>
#include <stdlib.h>
#include "searching.h"
#include "sorting.h"

void random_arr_gen(int arr[],int size) //generates random array
{
    for(int i=0;i<size;i++)
    {
        arr[i] = rand()%100; //values upto 100 only
    }
}

int main()
{
    int arr[] = {2,5,6,33,1,9};  //initial array
    int size = sizeof(arr)/sizeof(arr[0]);
    int menu=0,num=0;
    print_array(arr,size);
    printf("Menu Driven program for searching and sorting:\n");
    printf("1 for linear search\n");
    printf("2 for binary search\n");
    printf("3 for bubble sort\n");
    printf("4 for insertion sort\n");
    printf("5 for selection sort\n");
    printf("6 for merge sort\n");
    printf("7 for quick sort\n");
    printf("8 To Quit\n");
    
    do
    {
        printf("Enter the menu number: ");
        scanf("%d",&menu);
        printf("\n");
        switch (menu)
        {
            case 1:
            printf("Enter the number to be searched: ");
            scanf("%d",&num);
            printf("Found at index: %d\n",linear_search(arr,size,num)); break;

            case 2: 
            printf("Enter the number to be searched: ");
            scanf("%d",&num);
            bubbleSort(arr,size);
            printf("Found at index: %d\n",binary_search(arr,num,size)); break;

            case 3: 
            printf("Original array: ");
            random_arr_gen(arr,size);
            print_array(arr,size);
            bubble_sort(arr,size);
            printf("After sort: ");
            print_array(arr,size); break;

            case 4:
            printf("Original Array: ");
            random_arr_gen(arr,size);
            print_array(arr,size); 
            insertion_sort(arr,size);
            printf("After sort: "); 
            print_array(arr,size); break;

            case 5:
            printf("Original Array: ");
            random_arr_gen(arr,size); 
            print_array(arr,size);
            selection_sort(arr,size);
            printf("After sort: "); 
            print_array(arr,size); break;

            case 6:
            printf("Original Array: ");
            random_arr_gen(arr,size); 
            print_array(arr,size);
            mergeSort(arr,0,size);
            printf("After sort: "); 
            print_array(arr,size); break;

            case 7:
            printf("Original Array: ");
            random_arr_gen(arr,size); 
            print_array(arr,size);
            quickSort(arr,0,size);
            printf("After sort: "); 
            print_array(arr,size); break;

            default: break;
        }

    } while(menu!=8);
    printf("Exited from menu driven program\n");
    return 0;
}