#include "csapp.h"
void *thread(void *vargp);

int main(int ac, char **av)
{
	pthread_t tid[MAXBUF];

	if (ac != 2) {
		return 0;
	}

	int n = atoi(av[1]);
	for (int i = 0; i < n; i++)
		Pthread_create(&tid[i], NULL, thread, NULL);
	for (int i = 0; i < n; i++)
		Pthread_join(tid[i], NULL);
	// Pthread_exit(NULL);
	exit(0);
	
}

void *thread(void *vargp)
{
	printf("Hello, world!\n");
	return NULL;
}
