#define MAX_SIZE 100

typedef struct Edge
{
    int u;
    int v;
    int weight;
} Edge;

typedef struct 
{
    Edge items[MAX_SIZE];
    int size;
} PriorityQueue;

Edge edge(int u,int v,int weight);
PriorityQueue* createMinPriorityQueue();
void destroyMinPriorityQueue(PriorityQueue* queue);
void insert(PriorityQueue* queue, Edge item);
int is_Empty(PriorityQueue* queue);
Edge deleteMin(PriorityQueue* queue);
