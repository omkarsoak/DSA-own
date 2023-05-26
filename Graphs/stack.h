typedef struct snode
{
    int data;
    struct snode *next;
}snode;

typedef snode* stack;
void displayStack(snode* ptr);
int is_empty(snode* top);
int is_full(snode* top);
void push(snode** top,int data);
int pop(snode** top);
int peek(snode* top);