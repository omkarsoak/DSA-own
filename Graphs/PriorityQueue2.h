#define MAX_SIZE 100

typedef struct Pair
{
    int u;
    int distance;
} Pair;

typedef struct 
{
    Pair items[MAX_SIZE];
    int size;
} PriorityQueue2;

Pair pair(int u,int distance);
PriorityQueue2* createMinPriorityQueue2();
void destroyMinPriorityQueue2(PriorityQueue2* queue);
void insert2(PriorityQueue2* queue, Pair item);
int is_Empty2(PriorityQueue2* queue);
Pair deleteMin2(PriorityQueue2* queue);
