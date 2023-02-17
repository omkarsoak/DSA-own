#include <stdio.h>
int linear_search(int arr[], int size, int key)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(int arr[], int key, int high)
{
    int low=0,mid=0;
    while(low<=high)
    {
        mid = low + (high-low)/2;
        if (key == arr[mid])
        {
            return mid;
        }         
        else if (key > arr[mid])
        {
            low = mid + 1;
        }
        else if(key > arr[mid])  
        {
            high = mid - 1;
        }                               
    }
    return -1;
}