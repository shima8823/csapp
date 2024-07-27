#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *environ[]) {
	printf("Command-line arguments:\n");
	for (int i = 0; i < argc; i++) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	printf("Environment variables:\n");
	for (int i = 0; environ[i]; i++) {
		printf("envp[%d]: %s\n", i, environ[i]);
	}

}