#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"
#include "stack.h"

typedef struct graph
{
    int** arr;
    int n;
}graph;

typedef struct node
{
    int vertex;
    int weight;
    struct node* next;
}node;

typedef struct adjList
{
    int n;
    node** adj;
}adjList;

node* createNode(int vertex,int weight)
{
    node* nn = (node*)malloc(sizeof(node));
    nn->vertex = vertex;
    nn->weight = 1;
    nn->next = NULL;
    return nn;
}

adjList* createGraph(int n)
{
    adjList* newGraph = (adjList*)malloc(sizeof(adjList));
    newGraph->n = n;
    newGraph->adj = (node**)malloc(sizeof(node*)*n);

    for(int i=0;i<newGraph->n;i++)
    {
        newGraph->adj[i] = NULL;
    }
    return newGraph;
}

//for undirected graph - add both u->v and v->u
void addEdge(adjList* g,int u,int v,int weight)
{
    node* newnode1 = createNode(v,weight);
    newnode1->next = g->adj[u];
    g->adj[u] = newnode1;

    node* newnode2 = createNode(u,weight);
    newnode2->next = g->adj[v];
    g->adj[v] = newnode2;
}

void printAdjList(adjList* g)
{
    for(int i=0;i<g->n;i++)
    {
        printf("%d: ",i);
        node* ptr = g->adj[i];
        while (ptr!=NULL)
        {
            printf("%d, ",ptr->vertex);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

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
    queue* q = initialize_queue();    //exploration queue
    int* visited = (int*)calloc(g->n,sizeof(int));  //visitied array with all elements init to 0
    visited[start] = 1;
    enqueue(q,start);
    
    while(isEmpty(q)!=1)
    {
        int curr = dequeue(q);   //dequeue node to explore
        printf("%d ",curr);
        
        for(int i=0;i<g->n;i++)
        {
            if(g->arr[curr][i]==1 && visited[i]==0)   //if edge present & not visited
            {
                visited[i] = 1;
                enqueue(q,i);
            }
        }
    }
}

void DFS(graph* g,int start)
{
    stack s = NULL;
    int* visited = (int*)calloc(g->n,sizeof(int));  //visitied array with all elements init to 0
    visited[start] = 1;

    push(&s,start);
    while (is_empty(s)!=1)
    {
        int curr = pop(&s);
        printf("%d ",curr);
        for(int i=0;i<g->n;i++)
        {
            if(g->arr[curr][i]==1 && visited[i]==0)   //if edge present & not visited
            {
                visited[i] = 1;
                push(&s,i);
            }
        }
    } 
}


//recursive DFS
void dfs_helper(graph* g,int* visited,int node)
{
    visited[node] = 1;
    printf("%d ",node);
    for(int i=0;i<g->n;i++)
    {
        if(g->arr[node][i]==1 && visited[i]==0)   //if edge present & not visited
        {
            dfs_helper(g,visited,i);
        }
    }
}

void dfs(graph* g,int start)
{
    int* visited = (int*)calloc(g->n,sizeof(int));  //visitied array with all elements init to 0
    dfs_helper(g,visited,start);
}

int isConnected(graph* g,int start)
{
    stack s = NULL;
    int* visited = (int*)calloc(g->n,sizeof(int));  //visitied array with all elements init to 0
    visited[start] = 1;

    push(&s,start);
    while (is_empty(s)!=1)
    {
        int curr = pop(&s);
        printf("%d ",curr);
        for(int i=0;i<g->n;i++)
        {
            if(g->arr[curr][i]==1 && visited[i]==0)   //if edge present & not visited
            {
                visited[i] = 1;
                push(&s,i);
            }
        }
    }

    for(int i=0;i<g->n;i++)
    {
        if(visited[i]==0)
        {
            return 0;
        }
    }
    return 1;
}

adjList* Prims(graph* g,int start)
{
    adjList* MST = createGraph(g->n);
    int* visited = (int*)calloc(g->n,sizeof(int));
    visited[start]=1;

    //int curr = start;
    int min = INT_MAX;
    int minNode = start;
    int prev_p;
    for(int i=0;i<g->n-1;i++)
    {
        for(int p=0;p<g->n;p++)
        { 
            if(visited[p]!=0)
            {
                for(int j=0;j<g->n;j++)
                {
                    if(g->arr[p][j]!=0 && visited[p]!=0 && visited[j]==0)
                    {
                        if(g->arr[p][j]<min)
                        {
                            min = g->arr[p][j];
                            minNode = j;
                            prev_p = p;
                        }
                    }
                }
            }
            
        }
        addEdge(MST,prev_p,minNode,min);
        visited[minNode]=1;
        //curr = minNode;
        
    }
    return MST;
}

int main()
{
    graph* g1 = initGraph("data.txt");
    //display(g1);

    //int* degrees;
    //degrees = display_degree(g1);
    //print_array(degrees,g1->n);

    //BFS(g1,0);
    //printf("\n");
    //DFS(g1,0);
    //printf("\n");
    //dfs(g1,0);

    //adjList* ans = Prims(g1,0);
    //printAdjList(ans);

    printf("is: %d ",isConnected(g1,0));





    return 0;
}
