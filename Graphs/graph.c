#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int** arr;
    int size;
}graph;

void initGraph(graph* g,char* filename)
{
    FILE *fp = fopen(filename,"r");  //open file
    if(!fp) return;

    fscanf(fp,"%d",&g->size);

    g->arr = (int**)malloc(sizeof(int*)*g->size);
    
    for(int i=0;i<g->size;i++)
    {
        g->arr[i]=(int*)malloc(sizeof(int)*g->size);
        
        for(int j=0;j<g->size;j++)
        {
            fscanf(fp,"%d",&g->arr[i][j]);
        }
    }

    fclose(fp);
    return;
}

void display(graph* g)
{
    for(int i=0;i<g->size;i++)
    {
        for(int j=0;j<g->size;j++)
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
    for (int i=0; i<g->size; i++)   
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
    int* degrees = (int*)malloc(sizeof(int)*g->size);
    for(int i=0;i<g->size;i++)
    {
        degrees[i] = findDegree(g,i);
    }
    return degrees;
}

void print_array(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main()
{
    graph g1;
    initGraph(&g1,"data2.txt");
    display(&g1);

    int* degrees;
    degrees = display_degree(&g1);
    print_array(degrees,g1.size);

    return 0;
}
