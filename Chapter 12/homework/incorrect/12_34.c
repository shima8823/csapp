// 時間切れ

// #include "csapp.h"

// #define N 4
// #define M 4


// void *handler(void *arg) {
	
// }

// void thread_caluculator(int **a, int **b) {
// 	int ans[N][M];
// 	pthread_t tid[N * M];

// 	for (size_t i = 0; i < N; i++) {
// 		for (size_t j = 0; j < M; j++) {
// 			int *number_list = malloc(sizeof(int) * (N * 2));
// 			if (number_list == NULL)
// 				unix_error("malloc");
// 			number_list[0] = a[0][0];
// 			number_list[1] = b[0][0];
// 			Pthread_create(&tid[i*N + j], NULL, handler, );
// 		}
// 	}
	

// 	for (size_t i = 0; i < N; i++) {
// 		for (size_t j = 0; j < M; j++) {
// 			int ret;
// 			Pthread_join(&tid[i*N + j], &ret);
// 			ans[i][j] = ret;
// 			printf("%d ", ret);
// 		}
// 		printf("\n");
// 	}
	

// }

// int main(int argc, char const *argv[])
// {
// 	if (argc != 3) {
// 		fprintf(STDERR_FILENO, "usage: ./a.out 1 2");
// 		return 1;
// 	}

// 	int a[N][M];
// 	int b[N][M];

// 	for (size_t i = 0; i < N; i++)
// 	{
// 		for (size_t j = 0; j < M; j++)
// 		{
// 			a[i][j] = rand() % 6;
// 			b[i][j] = rand() % 6;
// 		}
		
// 	}
	
// 	thread_caluculator(a, b);
// 	return 0;
// }


// /*
//  * 12.34.concurrent.c
//  */
#include "csapp.h"
#define N 1600
#define M 1600

#define THREAD (1<<4)
#define ROWS_PER_THREAD (N / THREAD)


int M1[N][M];
int M2[N][M];

int MUL12[N][M];

void *thread_mul(void *vargp) {
  int idx = *(int*)vargp;
  int start = ROWS_PER_THREAD * idx;
  int i, j, k;
  for (i = start; i < start+ROWS_PER_THREAD; i++)
    for (j = 0; j < N; j++) {
      int sum = 0;
      for (k = 0; k < M; k++) {
        sum += M1[i][k] * M2[k][j];
      }
      MUL12[i][j] = sum;
    }
}

void concurrent_mul(void) {
  pthread_t tid[THREAD];
  int param[THREAD];
  int i;

  for (i = 0; i < THREAD; i++) {
    param[i] = i;
    Pthread_create(&tid[i], NULL, thread_mul, &param[i]);
  }
  for (i = 0; i < THREAD; i++) {
    Pthread_join(tid[i], NULL);
  }
}

void non_concurrent_mul(void) {
  int i, j, k;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      int sum = 0;
      for (k = 0; k < M; k++) {
        sum += M1[i][k] * M2[k][j];
      }
      MUL12[i][j] = sum;
    }
}

int main(int argc, char* argv[]) {
	if (atoi(argv[1]) == 1) {
		concurrent_mul();
	} else if (atoi(argv[1]) == 0) {
		non_concurrent_mul();
	}
  return 0;
}


