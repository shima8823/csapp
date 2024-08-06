#include "csapp.h"

int main(int argc, char **argv) 
{
	int n;
	rio_t rio;
	char buf[MAXLINE];

	if (argc > 1) {
		int fd = Open(argv[1], O_RDONLY, S_IRUSR);
		if (fd < 0) {
			fprintf(stderr, "invalid file %s\n", argv[1]);
			exit(0);
		}
		Dup2(fd ,STDIN_FILENO);
	}

	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) 
		Rio_writen(STDOUT_FILENO, buf, n);
	exit(0);
}
