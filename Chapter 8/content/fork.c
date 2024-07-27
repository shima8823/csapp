#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// int main() {
// 	pid_t pid;
// 	int x = 1;

// 	pid = fork();
// 	if (pid == 0) {
// 		printf("child: x=%d\n", ++x);
// 		exit(0);
// 	}
// 	printf("parent: x=%d\n", --x);
// 	exit(0);
// }
int main() {
	static int a = 0;
	fork();
	a++;
	pid_t p = fork();
	if (p == 0)
		a++;
	printf("hello %d\n", a);
	exit(0);
}