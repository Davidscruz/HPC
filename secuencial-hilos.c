#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>


//Variables globales
int num_hilos = 4;
int fil = 1000, col=1000;
double** A;
double** B;
double** C;

//Funcion de leer matriz
void read_mat(int col, int fil);

//Función de imprimir resultado
void print_result();

//Funcion paralela
void *matmul(void* rank);

int main(int argc, char* argv[]){
  
  pthread_t tid[num_hilos];
  int i, j; 
  long rank;

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
  
  //Creación de hilos
  for (rank = 0; rank < num_hilos; rank++)
     pthread_create(&tid[rank], NULL,matmul , (void*) rank);

  //Unión de hilos
  for (rank = 0; rank < num_hilos; rank++)
      pthread_join(tid[rank], NULL);

  //Impresión de resultado
  print_result();

  //Liberación de memoria
  free(A);
  free(B);
  free(C);

  // Fin de proceso padre
  pthread_exit(NULL);
  return 0;
}

//-------------------------------------------
// Función que va ejecutarse en cada hilo
void *matmul(void* id_arg){
  int i,j,k;
  long  id = (long ) id_arg;
  int filas_por_hilo = col/num_hilos;
  int start_index = id*filas_por_hilo;
  int final_index = (id+1)*filas_por_hilo;

  for(i=start_index;i<final_index;i++){
   for(j=0;j<col;j++){
    for(k=0;k<fil;k++){
      C[i][j] += A[i][k]*B[k][j]; 
    }
   }
  }
}
//--------------------------------------------
void read_mat(int col, int fil){
  int i,j;
  
  
  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){
      		A[i][j] = rand() % 10;
      		B[i][j] = rand() % 10;	
      }
       printf("\n");
   }

}

void print_result(){
  int i,j;
  
	struct timeval start;
  	struct timeval end;
  	double milisecs;
  	long seconds, useconds;
  
  //capturar el tiempo para medir el tiempo de ejecucción
  gettimeofday(&start, 0);
  
  //Imprimir la matriz resultado
  printf("\n Matriz resultado: \n");
  for(i = 0; i < fil; i++){
      for(j = 0; j < col; j++){ 
         printf("%.0lf ",C[i][j]); 
       }
      printf("\n");
   }
   
   gettimeofday(&end, 0);
   
   //imprimir el tiempo de ejecución en milisegundos
   
   seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  milisecs = ((seconds) * 1000 + useconds/1000.0);
  printf("Tiempo de ejecucion:\t");
  printf("%.16g milisegundos\n", milisecs );

}