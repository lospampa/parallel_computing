#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 8

void initVector(int *A, int *B, int *C){
    for(int i = 0; i < N; i++){
        A[i] = i;
        B[i] = N - i;
        C[i] = 0;
    }
}

void addVector(int *A, int *B, int *C){
    #pragma omp parallel
    {
        for(int i = 0; i < N; i++){
            C[i] = A[i] + B[i];
            printf("Thread %d calculating C[%d] = A[%d] + B[%d]\n", omp_get_thread_num(), i, i, i);
        }   
    }
}


int main(int argc, char **argv){

    int *A, *B, *C;
    A = malloc(sizeof(int)*N);
    B = malloc(sizeof(int)*N);
    C = malloc(sizeof(int)*N);
    
    initVector(A, B, C);

    addVector(A, B, C);

    return 0;
}