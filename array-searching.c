#include<stdio.h>
#include<stdlib.h>
int linear_search(int arr[],int size,int element)
{
    for(int i=0;i<=size;i++)
    {
        if(arr[i]==element)
        {return i;}
    }
    return -1;
}

int binary_search(int arr[],int size,int element)
{
    int low=0,high=(size-1),mid;
    while(low<=high)   //keep searching until low and high converges
    {
        mid = (low + high)/2;
        if(arr[mid]==element)
        {return mid;}
        else if(arr[mid]<element)
        {low=mid+1;}
        else if(arr[mid]>element)
        {high=mid-1;}
    }
    return -1;
}

int main()
{
    int arr1[] = {2,6,3,5,7,4,3,8,22};
    int size=(sizeof(arr1)/sizeof(int));
    int element = 7;
    int search_index = linear_search(arr1,size,element);
    printf("The element is found at index: %d\n",search_index);

    int arr2[] = {1,2,5,7,9,12,15,21};  //sorted array
    size = (sizeof(arr2)/sizeof(int));
    element = 12;
    search_index = binary_search(arr2,size,element);
    printf("The element is found at index: %d\n",search_index);

    return 0;
}