/*CONTAINS 5 SORTING ALGORITMS & AUXILLARY FUNCTIONS

**AUXILLARY FUNCTIONS**
*SWAP()
*PRINT ARRAY()

**SORTS**
*BUBBLE SORT - ITERATIVE & RECURSIVE 
*INSERTION SORT - ITERATIVE & RECURSIVE
*SELECTION SORT - ITERATIVE & RECURSIVE 
*MERGE SORT - merge() & mergeSort()
*QUICK SORT - partition() & quickSort()

AUTHOR: OMKAR OAK
*/
#include <stdio.h>

/*AUXILLARY FUNCTIONS*/
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

/*BUBBLE SORT*/
void bubble_sort(int arr[],int n)  //iterative
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}

void bubbleSort(int arr[],int n)  //recursive
{
    if (n == 1) //exit condition (for recursion)
        return;
    for(int i=0;i<n-1;i++)
    {
        if(arr[i]>arr[i+1])
        {
            swap(&arr[i],&arr[i+1]);
        }
    }
    bubbleSort(arr,n-1);
}

/*INSERTION SORT*/
void insertion_sort(int arr[],int n) //iterative (copy method)
{
    int j,key;
    for(int i=1;i<n;i++)
    {
        key=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j]=key;
    }
}

void insertionSort(int arr[],int n) //recursive
{
    if(n<1)
    {
        return;
    }
    insertionSort(arr,n-1);
    int key = arr[n - 1];
    int j = n - 2;
    while (j >= 0 && arr[j] > key) {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = key;
}

/*SELECTION SORT*/
void selection_sort(int arr[],int n)  //iterative
{
    for(int i=0;i<n;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min])
            {
                min = j;
            }
        }
        swap(&arr[i],&arr[min]);
    }
}

void selectionSort(int arr[],int i,int n)  //recursive
{
    if(i>n)
    {
        return;
    }
    int min=i;
    for(int j=i+1;j<n;j++)
    {
        if(arr[j]<arr[min])
        {
            min = j;
        }
    }
    swap(&arr[i],&arr[min]);
    selectionSort(arr,i+1,n);
    
}

/*MERGE SORT*/
void merge(int A[],int low,int mid,int high)
{
    int i,j,k;
    int size = high;
    int B[size];  //auxillary array
    i=low,j=mid+1,k=low;
    while(i<=mid && j<=high)  //comparing ele at i & j
    {
        if(A[i]<=A[j])
        {
            B[k]=A[i];
            i++;
        }
        else
        {
            B[k]=A[j];
            j++;
        }
        k++;
    }
    while(i<=mid)  //dump remaining elements from i side
    {
        B[k]=A[i];
        i++;k++;
    }
    while(j<=high)  //dump remaining elements from j side
    {
        B[k]=A[j];
        j++;k++;
    }
    for(int i=low;i<=high;i++)  //copy B[] into A[]
    {
        A[i]=B[i];
    }
}

void mergeSort(int A[],int low,int high)
{
    int mid=0;
    if(low<high)  //exit condition (for recursion)
    {
        mid = low+ (high-low)/2;
        mergeSort(A,low,mid);   //dividing into parts during unfolding
        mergeSort(A,mid+1,high);
        merge(A,low,mid,high);  //sorting and merging sorted arrays during folding
    }
}

/*QUICK SORT*/
int partition(int arr[],int low,int high)
{
    int pivot = arr[low];  //set pivot as 1st element
    int i = low + 1;
    int j = high;
    while(i<=j)
    {                      //comparing
        if(arr[i]<=pivot)
        {
            i++;
        }
        else if(arr[j]>pivot)
        {
            j--;
        }
        else
        {
            swap(&arr[i],&arr[j]);
        }
        
    }

    swap(&arr[low],&arr[j]);  //Move the pivot element to its correct position

    return j;  //index of pivot element after partition
}

void quickSort(int arr[],int low,int high)
{
    int partition_index;
    if(low<high)  //exit condition (for recursion)
    {
        partition_index = partition(arr,low,high);
        quickSort(arr,low,partition_index-1);  //sort lower elements
        quickSort(arr,partition_index+1,high);  //sort higher elements
    }
}