typedef struct disjointSet
{
    int* rank;
    int* parent;
    int* size;
    int n;
}disjointSet;

disjointSet* DisjointSet_init(int n);
//finding ultimate parent
int findUparent(int node,int* parent);
void unionByRank(disjointSet* s,int u,int v);
void unionBySize(disjointSet* s, int u, int v);
void print_Array(int* arr,int n);