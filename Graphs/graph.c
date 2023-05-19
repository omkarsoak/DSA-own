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


int main()
{
    graph g1;
    initGraph(&g1,"data.txt");
    display(&g1);

    return 0;
}