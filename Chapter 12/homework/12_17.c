/*

A. プロセスがスレッドを作り終えた後1秒経つ前に終了しているから。

*/




/* 
 * hellobug.c - "hello, world" program with a bug
 */
/* $begin hellobug */
/* WARNING: This code is buggy! */
#include "csapp.h"
void *thread(void *vargp);

int main() 
{
    pthread_t tid;

    Pthread_create(&tid, NULL, thread, NULL);
    Pthread_exit(NULL);
	// or
	// Pthread_join(tid, NULL);
}

/* Thread routine */
void *thread(void *vargp) 
{
    Sleep(1);
    printf("Hello, world!\n"); 
    return NULL;
}
/* $end hellobug */