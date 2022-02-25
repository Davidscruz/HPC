#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>



/* gcc -osecuencial MatMulSecuencial.c
   ./secuencial
*/
int n;


int fil, col;
double** A;
double** B;
double** C;

//Funciones 
void read_mat(int col, int fil);
void matmul(int col, int fil);
void print_result();

int main(int argc, char* argv[]){
  int n;
  //printf("Ingresa el tamaño de la matriz: ");
  //scanf("%d", &n);
  //printf("Number: %d", n);
  srand(time(NULL));
  fil = n;
  col = n;
  int i, j;

  A = malloc(fil*sizeof(double*));
      for(i=0;i<fil;i++)
        A[i]=malloc(col*sizeof(double));

  B = malloc(fil*sizeof(double*));
      for(i=0;i<fil;i++)
        B[i]=malloc(col*sizeof(double));

  C =  malloc(fil*sizeof(double*));
      for(i=0;i<fil;i++)
        C[i]=malloc(col*sizeof(double));

  //Lectura de matrices
  read_mat(col,fil);

  struct timeval start;
  struct timeval end;
  double milisecs;
  long seconds, useconds;

  gettimeofday(&start, 0);

  //Realizar la multiplicacion
  matmul(col, fil);

  gettimeofday(&end, 0);

  //Impresión de resultado
  print_result(col,fil);
  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  milisecs = ((seconds) * 1000 + useconds/1000.0);
  printf("Tiempo de ejecucion:\t");
  printf("%8.3f milisegundos\n", milisecs );

  //Liberación de memoria
  free(A);
  free(B);
  free(C);

  return 0;
}


void matmul(int col, int fil){
  int i,j,k;

  for(i=0;i<fil;i++){
   for(j=0;j<col;j++){
    C[i][j]=0;
    for(k=0;k<col;k++){
      C[i][j] += A[i][k]*B[k][j];
    }
   }
  }

}

void read_mat(int col, int fil){
  int i,j;

  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
       A[i][j] = rand() % 10;
      }
   }

  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
         B[i][j] = rand() % 10;
       }

   }
}

void print_result(int col, int fil){
  int i,j;

  //printf("Matriz C : \n");
  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
         //printf("%.0lf ", C[i][j]);
       }
      //printf("\n");
   }
}
