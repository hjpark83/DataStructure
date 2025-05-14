#include <stdio.h>
#include <stdlib.h>

int main(void){
    int **matrix;
    int row, col;
    printf("Input the row: ");
    scanf("%d", &row);
    printf("Input the col: ");
    scanf("%d", &col);

    matrix = (int**)malloc(sizeof(int*)*row);
    for(int i=0; i<row; i++){
        matrix[i] = (int*)malloc(sizeof(int)*col);
    }

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix[i][j] = i*col+j;
        }
    }

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<row; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}