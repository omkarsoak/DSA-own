#include <stdio.h>
#include <stdlib.h>
#include "disjointSet.h"
disjointSet* DisjointSet_init(int n)
{
    disjointSet* s = (disjointSet*)malloc(sizeof(disjointSet));
    s->n = n;
    s->rank = (int*)calloc(s->n,sizeof(int));
    s->parent = (int*)calloc(s->n,sizeof(int));
    s->size = (int*)calloc(s->n,sizeof(int));
    for(int i=0;i<s->n;i++)
    {
        s->parent[i] = i;
    }
    return s;
}

//finding ultimate parent
int findUparent(int node,int* parent)
{
    if(node == parent[node])
    {
        return node;
    }
    return parent[node] = findUparent(parent[node],parent);
}

void unionByRank(disjointSet* s,int u,int v)
{
    int Uparent_u = findUparent(u,s->parent);
    int Uparent_v = findUparent(v,s->parent);
    if(Uparent_u==Uparent_v)   //belong to same component
    {
        return;
    }
    if(s->rank[Uparent_u] < s->rank[Uparent_v])    //rank of u is smaller
    {
        s->parent[Uparent_u] = Uparent_v;
    }
    else if(s->rank[Uparent_v] < s->rank[Uparent_u])   //rank of v is smaller
    {
        s->parent[Uparent_v] = Uparent_u;
    }
    else if(s->rank[Uparent_v] == s->rank[Uparent_u])   //equal rank
    {
        s->parent[Uparent_v] = Uparent_u;
        s->rank[Uparent_u] += 1;
    }
}

void unionBySize(disjointSet* s, int u, int v) 
{
    int Uparent_u = findUparent(u,s->parent);
    int Uparent_v = findUparent(v,s->parent);
    if(Uparent_u==Uparent_v)   //belong to same component
    {
        return;
    }
    if (s->size[Uparent_u] < s->size[Uparent_v])   //size of u smaller
    {
        s->parent[Uparent_u] = Uparent_v;
        s->size[Uparent_v] += s->size[Uparent_u];
    }
    else                    //size of v smaller or size of u=v
    {
        s->parent[Uparent_v] = Uparent_u;
        s->size[Uparent_u] += s->size[Uparent_v];
    }
}

void print_Array(int* arr,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}