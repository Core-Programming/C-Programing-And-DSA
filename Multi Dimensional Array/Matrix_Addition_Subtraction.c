#include <stdio.h>
#include <stdlib.h>

#define ROW 3
#define COL 5

int Matrix_C[ROW][COL];

int Matrix_A[ROW][COL]={
        {10, 20, 30, 40, 50},
        {60, 70, 80, 90, 100},
        {110, 120, 130, 140, 150}
    };

int Matrix_B[ROW][COL]={
        {110, 120, 130, 140, 150},
        {160, 170, 180, 190, 1100},
        {1110, 1120, 1130, 1140, 1150}
    };


void addition_indexwise_matrix(void);
void subtraction_indexwise_matrix();
void print_matrix(void);


int main(void){
    
    addition_indexwise_matrix();
    puts("Matrix Addition");
     print_matrix();

    subtraction_indexwise_matrix();
    puts("Matrix Subtraction");
    print_matrix();
   

    exit(0);
}
void print_matrix()
{
    int i, j;
    for(i = 0; i < ROW; ++i){
        for(j = 0; j < COL; ++j){
            printf("[%d]", Matrix_C[i][j]);
        }
        printf("\n");
    }
}
void subtraction_indexwise_matrix()
{
    int i, j;

    for(int i = 0; i < ROW; ++i){
        for(j = 0; j < COL; ++j)
            Matrix_C[i][j] = Matrix_B[i][j] - Matrix_A[i][j];
    }
}

void addition_indexwise_matrix()
{
    int i, j;

    for(int i = 0; i < ROW; ++i){
        for(j = 0; j < COL; ++j)
            Matrix_C[i][j] = Matrix_A[i][j] + Matrix_B[i][j];
    }
}
