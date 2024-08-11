//正解がわからない

// /*
//  * 12.19.c
//  */
// #include <stdio.h>
// #include "csapp.h"

// #define WRITE_LIMIT 100000
// #define PEOPLE 4

// static int readtimes;
// static int writetimes;
// static int readcnt;
// // if a reader is waiting when writing, reader first next round
// static int reader_first;
// sem_t *mutex, *w;

// void *reader(void *vargp) {
//   while (1) {
// 	if (readtimes > writetimes)
// 		continue;
//     P(mutex);
//     readcnt++;
//     if (readcnt == 1)
//       P(w);
//     V(mutex);

//     /* Critical section */
//     readtimes++;
//     reader_first = 0;
//     /* Critical section */

//     P(mutex);
//     readcnt--;
//     if (readcnt == 0)
//       V(w);
//     V(mutex);
//   }
// }

// void *writer(void *vargp) {
//   while (1) {
// 	if (readtimes < writetimes)
// 		continue;
//     P(w);

//     /* Critical section */
//     writetimes++;
//     if (writetimes == WRITE_LIMIT) {
//       printf("read/write: %d/%d\n", readtimes, writetimes);
//       exit(0);
//     }
//     /* Critical section */

//     V(w);
//   }
// }

// void init(void) {
//   readcnt = 0;
//   readtimes = 0;
//   writetimes = 0;
//   reader_first = 0;
//   Sem_init(&w, 0, 1);
//   Sem_init(mutex, 0, 1);
// }


// int main(int argc, char* argv[]) {
//   int i;
//   pthread_t tid;

//   init();

//   for (i = 0; i < PEOPLE; i++)
//     if (i%2 == 0)
//       Pthread_create(&tid, NULL, reader, NULL);
//     else
//       Pthread_create(&tid, NULL, writer, NULL);

//   Pthread_exit(NULL);
//   exit(0);
// }


// answer
/*
 * 12.20.c
 */
#include <stdio.h>
#include "csapp.h"

#define WRITE_LIMIT 100000
#define PEOPLE 20 // 10 reader and 10 writer
#define N 4

static int readtimes;
static int writetimes;
sem_t *mutex;
sem_t *readercnt;

void *reader(void *vargp) {
  while (1) {
    P(readercnt);
    P(mutex);

    readtimes++;

    V(mutex);
    V(readercnt);
  }
}

void *writer(void *vargp) {
  while (1) {
    P(mutex);

    writetimes++;
    if (writetimes == WRITE_LIMIT) {
      printf("read/write: %d/%d\n", readtimes, writetimes);
      exit(0);
    }

    V(mutex);
  }
}

void init(void) {
  readtimes = 0;
  writetimes = 0;
  Sem_init(&mutex, 0, 1);
  Sem_init(&readercnt, 0, N);
}


int main(int argc, char* argv[]) {
  int i;
  pthread_t tid;

  init();

  for (i = 0; i < PEOPLE; i++) {
    if (i%2 == 0)
      Pthread_create(&tid, NULL, reader, NULL);
    else
      Pthread_create(&tid, NULL, writer, NULL);
  }

  Pthread_exit(NULL);
  exit(0);
}



