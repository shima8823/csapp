#include "csapp.h"

sigjmp_buf buf;

void handler_child_terminate(int sig) {
	siglongjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream) {

	if (!sigsetjmp(buf, 0)) {
		Signal(SIGCHLD, handler_child_terminate);
		if (Fork() == 0) {
			Sleep(5);
			exit(0);
		}
		return fgets(s, size, stream);
	} else {
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
