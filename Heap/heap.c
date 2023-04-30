#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    int* arr;
    int last;   //index of last element
    int capacity;
}heap;

void swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_init(heap* h,int capacity)
{
    h->capacity = capacity;
    h->arr = (int*)malloc(sizeof(int)*capacity);
    h->last = -1;
}

int isfull(heap* h)
{
    if(h->last+1 == h->capacity)
        return 1;
    else
        return 0;
}

int isempty(heap* h)
{
    if(h->last == -1)
        return 1;
    else
        return 0;
}

void adjust(int* arr,int i)   //bottoms up approach
{
    if(i <= 0)   //recursion base case 
    {
        return;
    }
    
    int parent = (i-1)/2;
    //i = current node

    if(arr[parent] < arr[i])   //if parent value > current node value
    {
        swap(&arr[parent],&arr[i]);
        adjust(arr,parent);
    }
}

void insert(heap* h,int data)
{
    if(isfull(h)==1)
        return;
    
    //else insert
    h->last++;
    h->arr[h->last] = data;  //insert at last index

    adjust(h->arr,h->last);
}

void heapify(int* arr,int last,int i)
{
    int largest = i;      //root
    int left = 2*i + 1;   //left child
    int right = 2*i + 2;  //right child
    
    //finding out largest between root & 2 children
    if(arr[left] > arr[largest] && left < last)
    {
        largest = left;
    }
    if(arr[right] > arr[largest] && right < last)
    {
        largest = right;
    }
    
    if(largest != i)   //recursion base case (largest != root)
    {
        swap(&arr[i],&arr[largest]);
        heapify(arr,last,largest);
    }
}

int delete(heap* h)
{
    if(isempty(h)==1)
    {
        return -1;
    }

    int data = h->arr[0];
    h->arr[0] = h->arr[h->last];   //replace root by last element
    h->last--;  //delete last

    heapify(h->arr,h->last,0);   //call heapify for root
    return data;
}

void build_heap(int* arr,int size)
{
    for(int i=size;i>=0;i--)
    {
        heapify(arr,size,i);
    }
}

//effectively it is level order traversal
void print_heap(heap* h)   
{
    for(int i=0;i<=h->last;i++)
    {
        printf("%d ",h->arr[i]);
    }
    printf("\n");
}

void print_array(int* arr,int size)   
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}


int main()
{
    heap* h1;
    heap_init(h1,100);
    insert(h1,30);
    insert(h1,20);
    insert(h1,10);
    insert(h1,40);
    insert(h1,15);
    insert(h1,60);
    
    print_heap(h1);
    delete(h1);
    print_heap(h1);

    int arr1[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int size = sizeof(arr1)/sizeof(int);
    print_array(arr1,size);
    build_heap(arr1,size);
    print_array(arr1,size);
    return 0;
}