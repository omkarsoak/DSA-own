#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "PQ.h"
#include "disjointSet.h"
#include "PriorityQueue2.h"
#include <limits.h>

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
    nn->weight = weight;
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
            printf("%d(%d) ",ptr->vertex,ptr->weight);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void BFS(graph* g,int start)
{
    queue* q = initialize_queue();   //exploration queue
    int* visited = (int*)calloc(g->n,sizeof(int));   //visitied array with all elements init to 0
    visited[start] = 1;
    enqueue(q,start);

    while(isEmpty(q)!=1)
    {
        int curr = dequeue(q);   //dequeue node to explore
        printf("%d ",curr);
        
        node* ptr = g->adj[curr];  //to traverse the list of curr node
        while (ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            
            if(visited[adjacent]==0)   //if not visited
            {
                visited[adjacent] = 1;
                enqueue(q,adjacent);
            }
            ptr = ptr->next;
        }
    }
}


//iterative DFS
void DFS(graph* g,int start)
{
    stack s = NULL;
    int* visited = (int*)calloc(g->n,sizeof(int));   //visitied array with all elements init to 0
    visited[start] = 1;
    push(&s,start);

    while(is_empty(s)!=1)
    {
        int curr = pop(&s);   //dequeue node to explore
        printf("%d ",curr);
        
        node* ptr = g->adj[curr];  //to traverse the list of curr node
        while (ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            
            if(visited[adjacent]==0)   //if not visited
            {
                visited[adjacent] = 1;
                push(&s,adjacent);
            }
            ptr = ptr->next;
        }
    }
}


//recursive DFS
void dfs(graph* g,int i,int* visited)
{
    visited[i] = 1;
    printf("%d ",i);
    node* ptr = g->adj[i];
    while(ptr!=NULL)
    {
        int adjacent = ptr->vertex;
        if(visited[adjacent]==0)
        {
            dfs(g,adjacent,visited);
        }
        ptr = ptr->next;
    }
}

//application of DFS
int detectCycle(graph* g,int curr,int parent,int* visited)
{
    visited[curr] = 1;
    node* ptr = g->adj[curr];
    while (ptr!=NULL)
    {
        int adjacent = ptr->vertex;
        if(visited[adjacent]==0)
        {
            if(detectCycle(g,adjacent,curr,visited)==1)
            {
                return 1;
            }
        }
        else if(adjacent!=parent)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

int isCycle(graph* g,int* visited)
{
    int cycles = 0;
    for (int i = 0; i < g->n; i++)
    {
        if(visited[i]==0)
        {
            cycles += detectCycle(g,i,-1,visited);
        }
    }
    return cycles;
}

//Edge(u,v,weight) --> edge is v(parent)-->u(node)
int MSTprims(graph* g,int start)
{
    int MSTsum = 0;
    PriorityQueue* pq = createMinPriorityQueue();
    int* visited = (int*)calloc(g->n,sizeof(int));
    visited[start]=1;
    insert(pq,edge(start,-1,0));
    
    while(is_Empty(pq)!=1)
    {
        Edge min = deleteMin(pq);
        int curr = min.u;
        if(visited[curr]==0)    //not visited
        {
            printf("%d - %d (%d)\n",min.v,curr,min.weight);
            visited[curr]=1;
            MSTsum += min.weight;
        }
        

        node* ptr = g->adj[curr];   //iterate over adjacent edges
        while(ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            int weight = ptr->weight;
            if(visited[adjacent]==0)    //not visited
            {
                insert(pq,edge(adjacent,curr,weight));
            }
            ptr = ptr->next;
        }
    }
    return MSTsum;
}


//auxillary function
void edgeSort(Edge arr[], int size) 
{
    int i, j;
    Edge temp;
    for (i = 0; i < size - 1; i++) 
    {
        for (j = 0; j < size - i - 1; j++) 
        {
            if (arr[j].weight > arr[j + 1].weight) 
            {
                // Swap the edges if the current weight is greater than the next weight
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int MSTkruskals(graph* g)
{
    int size = g->n;
    Edge* edges = (Edge*)malloc(size*(size-1)*sizeof(Edge));
    int k=0;
    
    //extracting edges from adjacency list and storing in Edge array
    for(int i=0;i<g->n;i++)
    {
        node* ptr = g->adj[i];
        while(ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            int weight = ptr->weight;
            edges[k] = edge(adjacent,i,weight);
            k++;
            ptr = ptr->next;
        }
    }

    edgeSort(edges,k);   //sort the edges array (bubble sort)
    int MSTsum = 0;   //cost of MST
    disjointSet* ds = DisjointSet_init(g->n);

    //run for all edges
    for(int i=0;i<k;i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int wt = edges[i].weight;
        if(findUparent(u,ds->parent)!=findUparent(v,ds->parent))  //not connected
        {
            MSTsum += wt;
            printf("%d - %d (%d)\n",u,v,wt);
            unionBySize(ds,u,v);
        }
    }
    return MSTsum;
}

int* Dijkstras(graph* g,int start)
{
    PriorityQueue2* pq = createMinPriorityQueue2();
    int* distanceTo = (int*)malloc(sizeof(int)*g->n); 
    for(int i=0;i<g->n;i++)
    {
        distanceTo[i] = INT_MAX;  //infinite
    }
    distanceTo[start] = 0;
    
    insert2(pq,pair(start,0));

    while(is_Empty2(pq)!=1)
    {
        Pair top = deleteMin2(pq);
        int dist = top.distance;  //here,distance = distance from start
        int curr = top.u;

        node* ptr = g->adj[curr];
        while (ptr!=NULL)
        {
            int adjacent = ptr->vertex;
            int wt = ptr->weight;
            if(dist+wt < distanceTo[adjacent])
            {
                distanceTo[adjacent] = dist+wt;   //update distanceTo
                insert2(pq,pair(adjacent,distanceTo[adjacent]));
            }
            ptr = ptr->next;
        }
    }
    return distanceTo;
}


int main()
{
    graph* g1 = createGraph(9);
    addEdge(g1,0,1,2);
    addEdge(g1,0,2,4);
    addEdge(g1,0,3,6);
    addEdge(g1,1,2,5);
    addEdge(g1,2,3,1);
    addEdge(g1,3,7,4);
    addEdge(g1,2,4,2);
    addEdge(g1,3,5,3);
    addEdge(g1,4,5,1);
    addEdge(g1,4,8,3);
    addEdge(g1,4,6,5);
    addEdge(g1,5,6,4);
    
    printGraph(g1);

    //BFS(g1,0);
    //printf("\n");
    //DFS(g1,0);
    //printf("\n");

    //int* visited = (int*)calloc(g1->n,sizeof(int));   //visitied array with all elements init to 0
    //dfs(g1,0,visited);
    //printf("%d",isCycle(g1,visited));
    //printf("%d\n",MSTprims(g1,0));

    //printf("%d\n",MSTkruskals(g1));

    //int* distance = (int*)malloc(sizeof(int)*g1->n);
    int* arr = Dijkstras(g1,0);
    print_Array(arr,g1->n);

    return 0;
}