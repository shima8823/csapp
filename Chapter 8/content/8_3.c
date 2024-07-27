#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	if (fork() == 0)
		printf("a");
	else {
		printf("b");
		waitpid(-1, NULL, 0);
	}
	printf("c");
	exit(0);
}

/*
acbc
abcc
bacc

*/