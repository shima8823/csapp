/*

利点: mallocやfreeを使わないのでメモリ安全性がある。
補足: オーバーヘッドが削減できる。

欠点: スレッドの個数に応じてメモリを消費してしまうこと。

answer
※ポインタとintのサイズが同じである前提
Pthread_create(... , (void *)i);

int myid = (int)vargp;

*/


/* 
 * norace.c - fixes the race in race.c
 */
/* $begin norace */
#include "csapp.h"
#define N 4

void *thread(void *vargp);

int main() 
{
    pthread_t tid[N];
    int i, *ptr;

	int array[N];

    for (i = 0; i < N; i++) {
		array[i] = i;
        Pthread_create(&tid[i], NULL, thread, &array[i]);   //line:conc:norace:createthread3
    } //line:conc:norace:endloop
    for (i = 0; i < N; i++) 
        Pthread_join(tid[i], NULL);
    exit(0);
}

/* Thread routine */
void *thread(void *vargp) 
{
    int myid = *((int *)vargp); //line:conc:norace:assign
    // Free(vargp); 
    printf("Hello from thread %d\n", myid);
    return NULL;
}
/* $end norace */