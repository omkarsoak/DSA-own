/*SPARSE MATRIX REPRESENTATION USING LINKED LIST AND 2 ARRAYS
STRUCTURE:
- VERTICAL ARRAY FOR ROWS
- HORIZONTAL ARRAY FOR COLUMNS
- LINKED LIST NODE CONTAINING LINKS TO right & down (ORTHOGONAL LL)

FUNCTIONS:
- INITIALIZE SPARSE MATRIX FROM FILE
- INITIALIZE EMPTY SPARSE MATRIX
- ADD 2 SPARSE MATRICES
- SUBTRACT 2 SPARSE MATRICES
- TRANSPOSE A SPARSE MATRIX
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    int i,j;
    struct node *right;
    struct node *down;
}node;

typedef struct sparse{
    node** row;  //pointer to the array of pointers to node 
    node** col;  //pointer to the array of pointers to node
    int total_rows,total_cols;   //total number of rows and columns
}sparse;

//so, s->row[x], s->col[x] is a pointer to node, row[] and col[] are arrays

void insert_node(sparse* s,node* new_node, int i,int j);  //prototype (defined ahead)

node* new_node_create(int data,int i,int j)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->i = i;
    temp->j = j;
    temp->right = NULL;
    temp->down = NULL;
    return temp;
}

void initialize_matrix_from_file(sparse* s,char *filename)
{
    FILE *fp = fopen(filename,"r");  //open file
    if(!fp) return;

    //input total rows and cols
    int row1,row2;
    fscanf(fp,"%d\n",&row1);
    s->total_rows = row1;
    fscanf(fp,"%d\n",&row2);
    s->total_cols = row2;

    //create arrays with size = total_rows & total_cols respectively
    s->row = (node**)malloc(sizeof(node*)*(s->total_rows));
    s->col = (node**)malloc(sizeof(node*)*(s->total_cols));
    for(int i=0;i<s->total_rows;i++)   //initialize all pointers in the rows array to NULL
    {
        s->row[i]=NULL;
    }
    for(int i=0;i<s->total_cols;i++)   //initialize all pointers in the cols array to NULL
    {
        s->col[i]=NULL;
    }

    int value;
    node *new_node;
    for(int i = 0;i<(s->total_rows);i++)   //read data from file row wise
    {
        for(int j = 0;j<(s->total_cols);j++)
        {
            fscanf(fp,"%d",&value);
            if(value != 0){
                new_node = new_node_create(value,i,j);
                insert_node(s,new_node,i,j);
            }
        }
    }
    fclose(fp);
    return;
}

void initialize_matrix(sparse* s,int total_rows,int total_cols)
{
    s->total_rows = total_rows;
    s->total_cols = total_cols;

    //create arrays with size = total_rows & total_cols respectively
    s->row = (node**)malloc(sizeof(node*)*(s->total_rows));
    s->col = (node**)malloc(sizeof(node*)*(s->total_cols));
    for(int i=0;i<s->total_rows;i++)   //initialize all pointers in the rows array to NULL
    {
        s->row[i]=NULL;
    }
    for(int i=0;i<s->total_cols;i++)   //initialize all pointers in the cols array to NULL
    {
        s->col[i]=NULL;
    }
}

void insert_node(sparse* s,node* new_node, int i,int j)
{
    node* pr = s->row[i];  //row traversing pointer
    node* pc = s->col[j];  //col traversing pointer

    //setting row
    if(s->row[i] == NULL)   //1st node in row condition
    {
        s->row[i] = new_node;
    }
    else
    {
        pr = s->row[i];
        while(pr->right!=NULL)
        {
            pr = pr->right;
        }
        pr->right = new_node;
    }

    //setting column
    if(s->col[j] == NULL)   //1st node is column condition
    {
        s->col[j] = new_node;
    }
    else
    {
        pc = s->col[j];
        while(pc->down!=NULL)
        {
            pc = pc->down;
        }
        pc->down = new_node;
    }
}

void display(sparse s)
{
    printf("Total rows: %d\n",s.total_rows);
    printf("Total columns: %d\n",s.total_cols);

    printf("Row - Column - Data\n");
    node* p;
    for(int i=0;i<s.total_rows;i++)   //traverse row-wise
    {
        p = s.row[i];
        while(p!=NULL)
        {
            printf("%d\t %d\t %d\n", p->i, p->j, p->data);
            p = p->right;
        }
    }
}

sparse add_sparse_matrix(sparse s1,sparse s2)
{
    if(s1.total_rows!=s2.total_rows || s1.total_cols!= s2.total_cols)
    {
        printf("Addition not possible\n");   //invalid matrices
    }

    node* p1;
    node* p2;
    sparse res;  //resultant matrix
    initialize_matrix(&res,s1.total_rows,s1.total_cols);
    
    for(int i=0;i<s1.total_rows;i++)   //traverse row by row
    {
        p1 = s1.row[i];
        p2 = s2.row[i];
        while(p1!=NULL && p2!=NULL)
        {
            if(p1->j == p2->j)   //node with same i,j present in both matrices
            {
                int item = p1->data + p2->data;
                node* new_node = new_node_create(item,i,p1->j);
                insert_node(&res,new_node,i,p1->j);
                p1 = p1->right;
                p2 = p2->right;            
            }
            else if(p1->j < p2->j)  //node for j present in s1 but not in s2
            {
                int item = p1->data;
                node* new_node = new_node_create(item,i,p1->j);
                insert_node(&res,new_node,i,p1->j);
                p1 = p1->right;              
            }
            else if(p1->j > p2->j)  //node for j present in s2 but not in s1
            {
                int item = p2->data;
                node* new_node = new_node_create(item,i,p2->j);
                insert_node(&res,new_node,i,p1->j);
                p2 = p2->right;       
            }
        }

        //dump remaining nodes directly (similar to merge sort)
        while(p1==NULL && p2!=NULL)   
        {
            int item = p2->data;
            node* new_node = new_node_create(item,i,p2->j);
            insert_node(&res,new_node,i,p2->j);
            p2 = p2->right;
        }
    }
    return res;
}

//same as add but only difference is '-' inplace of '+'
sparse subtract_sparse_matrix(sparse s1,sparse s2)
{
    if(s1.total_rows!=s2.total_rows || s1.total_cols!= s2.total_cols)
    {
        printf("Subtraction not possible\n");   //invalid matrices
    }
    node* p1;
    node* p2;
    sparse res;
    initialize_matrix(&res,s1.total_rows,s1.total_cols);
    
    for(int i=0;i<s1.total_rows;i++)
    {
        p1 = s1.row[i];
        p2 = s2.row[i];
        while(p1!=NULL && p2!=NULL)
        {
            if(p1->j == p2->j)
            {
                int item = p1->data - p2->data;  //different than add()
                node* new_node = new_node_create(item,i,p1->j);
                insert_node(&res,new_node,i,p1->j);
                p1 = p1->right;
                p2 = p2->right;            
            }
            else if(p1->j < p2->j)
            {
                int item = p1->data;
                node* new_node = new_node_create(item,i,p1->j);
                insert_node(&res,new_node,i,p1->j);
                p1 = p1->right;              
            }
            else if(p1->j > p2->j)
            {
                int item = p2->data;
                node* new_node = new_node_create(item,i,p2->j);
                insert_node(&res,new_node,i,p1->j);
                p2 = p2->right;       
            }
        }
        while(p1==NULL && p2!=NULL)
        {
            int item = p2->data;
            node* new_node = new_node_create(item,i,p2->j);
            insert_node(&res,new_node,i,p2->j);
            p2 = p2->right;
        }
    }
    return res;
}

sparse transpose(sparse s)
{
    sparse res;  //resultant matrix
    initialize_matrix(&res,s.total_cols,s.total_rows);
    node* p1;

    //traverse s column-wise & add to resultant row-wise
    for(int i=0;i<s.total_cols;i++) 
    {
        p1 = s.col[i];
        while(p1!=NULL)
        {
            node* new_node = new_node_create(p1->data,p1->j,p1->i);  //i&j swapped
            insert_node(&res,new_node,p1->j,p1->i);  //i&j swapped
            p1 = p1->down;
        }   
    }
    return res;
}

int main()
{
    sparse s1,s2;
    sparse add_ans,sub_ans,transpose_ans;
    initialize_matrix_from_file(&s1,"file1.txt");
    initialize_matrix_from_file(&s2,"file2.txt");
    display(s1);
    display(s2);
    add_ans = add_sparse_matrix(s1,s2);
    sub_ans = subtract_sparse_matrix(s1,s2);
    transpose_ans = transpose(s1);
    display(add_ans);
    display(sub_ans);
    display(transpose_ans);
    return 0;
}