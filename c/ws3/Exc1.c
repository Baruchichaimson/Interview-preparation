#include <stdio.h>
#include <stdlib.h>

/***************************
 Exercise:  WS3
 Date: 	    05/08/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
int main() 
{
    int **matrix = (int **)malloc(5 * sizeof(int *));
    if (!matrix) 
    {
        perror("Failed to allocate matrix rows");
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        matrix[i] = (int *)malloc(10 * sizeof(int));
        if (!matrix[i]) 
        {
            perror("Failed to allocate matrix row");
            return 1;
        }
    }

    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            matrix[i][j] = i * 10 + j;
        }
    }

    int *rowSums = (int *)malloc(5 * sizeof(int));
    if (!rowSums) 
    {
        perror("Failed to allocate row sums");
        return 1;
    }

    for (int i = 0; i < 5; ++i) 
    {
        rowSums[i] = 0;
        for (int j = 0; j < 10; ++j) 
        {
            rowSums[i] += matrix[i][j];
        }
    }
  

/********************************************
print all the matrix and the sum of the rows 
********************************************/

    printf("The Matrix is (%dx%d):\n", 5, 10);
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nSum of each row:\n");
    for (int i = 0; i < 5; ++i) 
    {
        printf("Row %d sum = %d\n", i, rowSums[i]);
    }

/****************************
free the matrix 
****************************/
    free(rowSums);
    for (int i = 0; i < 5; ++i)
        free(matrix[i]);
    free(matrix);

    return 0;
}

