#include<stdio.h>
#include <stdlib.h>
void print_2D(int *arr, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", *(arr + i*cols + j));
        }
        printf("\n");
    }      
}

void initialize_matrix(int *sparse_matrix,char *filename)
{
    FILE *fp = fopen(filename,"r");
    if(!fp) return;
    int total_rows,total_cols,size,data;
    fscanf(fp,"%d\n",&total_rows);
    fscanf(fp,"%d\n",&total_cols);
    for(int i=0;i<total_rows;i++)
    {
        for(int j=0;j<total_cols;j++)
        {
            fscanf(fp,"%d",&data);
            if (data != 0)
				size++;
        }
        fscanf(fp,"\n");
    }
}

int main()
{
	// Assume 4x5 sparse matrix
	int sparseMatrix[4][5] =
	{
		{0 , 0 , 3 , 0 , 4 },
		{0 , 0 , 5 , 7 , 0 },
		{0 , 0 , 0 , 0 , 0 },
		{0 , 2 , 6 , 0 , 0 }
	};

	int size = 0;
	for (int i = 0; i < 4; i++)
    {
		for (int j = 0; j < 5; j++)
        {
			if (sparseMatrix[i][j] != 0)
				size++;
        }
    }
	// number of columns in compactMatrix (size) must be
	// equal to number of non - zero elements in
	// sparseMatrix
	int compactMatrix[3][size];

	// Making of new matrix
	int k = 0;
	for (int i = 0; i < 4; i++)
    {
		for (int j = 0; j < 5; j++)
        {
			if (sparseMatrix[i][j] != 0)
			{
				compactMatrix[0][k] = i;
				compactMatrix[1][k] = j;
				compactMatrix[2][k] = sparseMatrix[i][j];
				k++;
			}
        }
    }

    //print comapct matrix
    //initialize_matrix(sparseMatrix[0],file);
    print_2D(compactMatrix[0],3,size);
	return 0;
}
