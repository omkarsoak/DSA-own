#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct graph
{
    int** arr;
    int n;
    int edges;
}graph;

graph* initGraph(char* filename)
{
    graph* g = (graph*)malloc(sizeof(graph));
    FILE *fp = fopen(filename,"r");  //open file
    if(!fp) return NULL;

    fscanf(fp,"%d",&g->n);

    g->arr = (int**)malloc(sizeof(int*)*g->n);
    
    for(int i=0;i<g->n;i++)
    {
        g->arr[i]=(int*)malloc(sizeof(int)*g->n);
        
        for(int j=0;j<g->n;j++)
        {
            fscanf(fp,"%d",&g->arr[i][j]);
        }
    }

    fclose(fp);
    return g;
}

void display(graph* g)
{
    for(int i=0;i<g->n;i++)
    {
        for(int j=0;j<g->n;j++)
        {
            printf("%d\t",g->arr[i][j]);
        }
        printf("\n");
    }
    return;
}

int findDegree(graph *g, int ver)
{
    int degree = 0;        
    for (int i=0; i<g->n; i++)   
    {
        if (g->arr[ver][i] != 0)
            degree++;  
    } 

    //for self loop in graph
    if(g->arr[ver][ver] != 0)
        degree++;
    return degree;        
}

int* display_degree(graph* g)
{
    int* degrees = (int*)malloc(sizeof(int)*g->n);
    for(int i=0;i<g->n;i++)
    {
        degrees[i] = findDegree(g,i);
    }
    return degrees;
}

int check_ifAdjacent(graph* g,int ver1,int ver2)
{
    if(g->arr[ver1][ver2]!=0)
    {
        return 1;
    }
    else if(g->arr[ver2][ver1]!=0)
    {
        return 1;
    }
    return 0;
}

int check_ifConnected(graph* g)
{
    for(int i=0;i<g->n;i++)
    {
        for(int j=0;j<g->n;j++)
        {
            if(g->arr[i][j]==0 && i!=j)
            {
                return 0;
            }   
        }
    }
    return 1;
}

void print_array(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void BFS(graph* g,int start)
{
    queue* q = initialize_queue();
    int* visited = (int*)calloc(g->n,sizeof(int));
    visited[start] = 1;
    enqueue(q,start);
    
    int curr;
    while(isEmpty(q)!=1)
    {
        curr = dequeue(q);
        printf("%d ",curr);
        
        for(int i=0;i<g->n;i++)
        {
            if(g->arr[curr][i]==1 && visited[i]==0)
            {
                visited[i] = 1;
                enqueue(q,i);
            }
        }
    }
}

int main()
{
    graph* g1 = initGraph("data.txt");
    display(g1);

    //int* degrees;
    //degrees = display_degree(g1);
    //print_array(degrees,g1->n);

    BFS(g1,0);



    return 0;
}