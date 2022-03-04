#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>



//Funciones
void matmul(int ** A, int ** B, int ** C, int n, int i);
void create(int ** A, int ** B, int ** C, int n);
void read_mat(int ** A, int ** B, int n);
void print_result(int ** C, int n);

int main(int argc, char* argv[]){

    int n = 1400;
    int ** A;
    int ** B;
    int ** C;
    int i, j;

    A = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);
    B = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);
    C = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);

    for(i=0; i<n; i++){
        A = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);
        B = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);
        C = (int **) mmap(NULL, sizeof (int *)*n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,1,0);
    }



    //Lectura de matrices
    read_mat(A, B, n);

    struct timeval start;
    struct timeval end;
    double milisecs;
    long seconds, useconds;

    gettimeofday(&start, 0);

    //Realizar la multiplicacion
    create(A, B, C, n);

    gettimeofday(&end, 0);

    //Impresión de resultado

    print_result(C,n);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    milisecs = ((seconds) * 1000 + useconds/1000.0);
    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisecs );

    //Liberación de memoria
    free(A);
    free(B);
    free(C);

    return 1;
}

//-------------------------------------------

void matmul(int ** A, int ** B, int ** C, int n, int i){

    for(int j=0; j<n; j++){
        int sum = 0;
        for(int k=0; k<n; k++){
            sum += A[j][k] * B[k][j];
        }
        C[j][i] = sum;
    }

}
//---------------------------------------

void create(int ** A, int ** B, int ** C, int n){
    int status;
    pid_t p_id;

    for(int i = 0; i<n; i++){
        p_id = fork();
        if (p_id == 0){
            matmul(A, B, C, n, i);
            exit(1);
        }else continue;
    }
    for (int i = 0; i<n; i++) wait(&status);
}

//----------------------------------------
void read_mat(int ** A, int ** B, int n){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = rand() % 10;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            B[i][j] = rand() % 10;
        }

    }
}

void print_result(int ** C, int n){
    int i,j;
/*
  printf("Matriz A : \n");
  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
         printf("%.0lf ", A[i][j]);
       }
      printf("\n");
   }
  printf("Matriz B : \n");
  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
         printf("%.0lf ", B[i][j]);
       }
      printf("\n");
   }
   */

    printf("Matriz C : \n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}