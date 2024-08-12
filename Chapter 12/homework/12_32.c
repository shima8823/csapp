#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream) {
	fd_set read_set;
	struct timeval time;

	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	time.tv_sec = 5;

	Select(STDIN_FILENO+1, &read_set, NULL, NULL, &time);
	if (FD_ISSET(STDIN_FILENO, &read_set))
		return fgets(s, size, stream);
	return NULL;
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
