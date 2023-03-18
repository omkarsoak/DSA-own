/*******Linked list functions & definition**********/
typedef struct node
{
    int data;
    struct node* next;
}node;

//Linked list functions
void insert_at_begining(node** head_ref, int data);
void insert_at_end(node** head_ref,int data);
void delete_node_atValue(node** head_ref,int value);
void traverse_list(node* head);
int reverse_list(node** head_ref);
node* create_new_node(int data);
