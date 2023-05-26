typedef struct qnode
{
    int curr;
    int parent;
    struct qnode* next;
}qnode;

typedef struct queue
{
    qnode* front;
    qnode* rear;
}queue;

queue* initialize_queue();
int isEmpty(queue *q);
void enqueue(queue* q,int data);
int dequeue(queue* q);
void displayQueue(queue q);
