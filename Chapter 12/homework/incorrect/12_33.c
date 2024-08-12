// 良問 thread

#include "csapp.h"

struct arg_fgets {
	char *s;
	int size;
	FILE * stream;
};

char *buf;
int timeout = -1;

void *sleep_thread() {
	Sleep(5);
	timeout = 1;
	return NULL;
}

void *input_thread(void *arg) {
	struct arg_fgets fgets_arg = *((struct arg_fgets *)arg);
	buf = fgets(fgets_arg.s, fgets_arg.size, fgets_arg.stream);
	timeout = 0;
	return NULL;
}

char *tfgets(char *s, int size, FILE *stream) {	
	pthread_t tid_sleep, tid_input;

	struct arg_fgets arg;
	arg.s = s; arg.size = size; arg.stream = stream;

	Pthread_create(&tid_sleep, NULL, sleep_thread, NULL);
	Pthread_create(&tid_input, NULL, input_thread, &arg);

	while (timeout == -1) {}

	if (timeout == 0) {
		Pthread_cancel(tid_sleep);
		return buf;
	} else {
		Pthread_cancel(tid_input);
		return NULL;
	}
}

int main() 
{
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, stdin) == NULL)
		printf("BOOM!\n");
    else 
		printf("%s", buf);

    exit(0);
}
