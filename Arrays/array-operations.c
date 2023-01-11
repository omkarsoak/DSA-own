#include<stdio.h>
#include<stdlib.h>
//traversal
void display(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

//insertion
int insertion(int arr[],int size, int element, int index,int capacity)
{
    if(size>=capacity)  //out of bound error check
    {return -1;}
    for(int i=size-1;i>=index;i--)
    {
        arr[i+1]= arr[i];
    }
    arr[index] = element;
    return 1;
}

//deletion
int deletion(int arr[],int size,int index,int capacity)
{
    if(index>=capacity)  //out of bound error check
    {return -1;}
    for(int i=index;i<=size;i++)
    {
        arr[i]=arr[i+1];
    }
}

int main()
{
    int arr[100] = {7,8,4,15};
    display(arr,4);
    int size=4, element=22, index=2;
    insertion(arr,size,element,index,100);
    size++;
    display(arr,size);
    deletion(arr,size,index,100);
    size--;
    display(arr,size);

    return 0;
}
