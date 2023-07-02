/*SPARSE MATRIX ROW-COLUMN FORM*/

// Function to add two sparse matrices
void addSparseMatrices(int matrix1[][3], int size1, int matrix2[][3], int size2, int result[][3], int* size3) 
{
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) 
    {
        if (matrix1[i][0] < matrix2[j][0] || (matrix1[i][0] == matrix2[j][0] && matrix1[i][1] < matrix2[j][1])) 
        {
            //row1 < row2 or if row is equal, column1 < column2
            //copy mat1 entry
            result[k][0] = matrix1[i][0];
            result[k][1] = matrix1[i][1];
            result[k][2] = matrix1[i][2];
            i++;
        } 
        else if (matrix1[i][0] > matrix2[j][0] || (matrix1[i][0] == matrix2[j][0] && matrix1[i][1] > matrix2[j][1]))
        {
            //row1 > row2 or if row is equal, column1 > column2
            //copy mat2 entry

            result[k][0] = matrix2[j][0];
            result[k][1] = matrix2[j][1];
            result[k][2] = matrix2[j][2];
            j++;
        } 
        else   //same row column - add both entries
        {
            result[k][0] = matrix1[i][0];
            result[k][1] = matrix1[i][1];
            result[k][2] = matrix1[i][2] + matrix2[j][2];
            i++;
            j++;
        }
        k++;
    }

    // Copy any remaining elements from matrix1
    while (i < size1) {
        result[k][0] = matrix1[i][0];
        result[k][1] = matrix1[i][1];
        result[k][2] = matrix1[i][2];
        i++;
        k++;
    }

    // Copy any remaining elements from matrix2
    while (j < size2) {
        result[k][0] = matrix2[j][0];
        result[k][1] = matrix2[j][1];
        result[k][2] = matrix2[j][2];
        j++;
        k++;
    }

    *size3 = k; // Update the size of the result matrix
}


void transposeSparseMatrix(int sparseMatrix[][3], int size, int transposedMatrix[][3]) 
{
    //row & column swap
    for (int i = 0; i < size; i++) 
    {
        transposedMatrix[i][0] = sparseMatrix[i][1];
        transposedMatrix[i][1] = sparseMatrix[i][0];
        transposedMatrix[i][2] = sparseMatrix[i][2];
    }

    //sort according to row (bubble sort)
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size - i; i++)
        {
            if(transposedMatrix[j][0] > transposedMatrix[j+1][0])
            {
                swap(transposedMatrix[j][0] , transposedMatrix[j+1][0]);
                swap(transposedMatrix[j][1] , transposedMatrix[j+1][1]);
                swap(transposedMatrix[j][2] , transposedMatrix[j+1][2]);
            }
        }
    }

}

int main()
{
    return 0;
}