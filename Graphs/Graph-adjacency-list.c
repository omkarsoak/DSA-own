#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node
{
    int vertex;
    int weight;
    struct node* next;
}node;

typedef struct graph
{
    int n;
    node** adj;
}graph;

node* createNode(int vertex,int weight)
{
    node* nn = (node*)malloc(sizeof(node));
    nn->vertex = vertex;
    nn->weight = 1;
    nn->next = NULL;
    return nn;
}

graph* createGraph(int n)
{
    graph* newGraph = (graph*)malloc(sizeof(graph));
    newGraph->n = n;
    newGraph->adj = (node**)malloc(sizeof(node*)*n);

    for(int i=0;i<newGraph->n;i++)
    {
        newGraph->adj[i] = NULL;
    }
    return newGraph;
}

//for undirected graph - add both u->v and v->u
void addEdge(graph* g,int u,int v,int weight)
{
    node* newnode1 = createNode(v,weight);
    newnode1->next = g->adj[u];
    g->adj[u] = newnode1;

    node* newnode2 = createNode(u,weight);
    newnode2->next = g->adj[v];
    g->adj[v] = newnode2;
}

//for directed graph - add only u->v
void AddEdge(graph* g,int u,int v,int weight)
{
    node* newnode = createNode(v,weight);
    newnode->next = g->adj[u];
    g->adj[u] = newnode;
}

void printGraph(graph* g)
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

void BFS(graph* g,int start)
{
    queue* q = initialize_queue();
    int* visited = (int*)calloc(g->n,sizeof(int));
    visited[start] = 1;
    enqueue(q,start);

    while(isEmpty(q)!=1)
    {
        int curr = dequeue(q);
        printf("%d ",curr);
        
        node* ptr = g->adj[curr];
        while (ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            
            if(visited[adjacent]==0)
            {
                visited[adjacent] = 1;
                enqueue(q,adjacent);
            }
            ptr = ptr->next;
        }
    }
}

int main()
{
    graph* g1 = createGraph(8);
    addEdge(g1,0,1,1);
    addEdge(g1,1,2,1);
    addEdge(g1,0,2,1);
    addEdge(g1,2,3,1);
    addEdge(g1,3,4,1);
    addEdge(g1,3,5,1);
    addEdge(g1,3,6,1);
    addEdge(g1,6,5,1);
    addEdge(g1,4,5,1);
    addEdge(g1,5,7,1);
    
    printGraph(g1);

    BFS(g1,0);
    return 0;
}