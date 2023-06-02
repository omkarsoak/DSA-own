typedef struct qnode2
{
    int curr;
    int parent;
    struct qnode2* next;
}qnode2;

typedef struct queue2
{
    qnode2* front;
    qnode2* rear;
}queue2;

queue2* initialize_queue2();
int isEmpty(queue2 *q);
void enqueue2(queue2* q,int curr,int parent);
void dequeue2(queue2* q);
qnode2* peekFront(queue2* q);
void displayqueue2(queue2 q);
