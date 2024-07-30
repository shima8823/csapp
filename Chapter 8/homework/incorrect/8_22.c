#include "csapp.h"

int mysystem(char *command) {
	int status;
	pid_t pid = Fork();
	if (pid == 0) {
		char *argv[4] = {"", "-c", command, NULL};
		execve("/bin/sh", argv, environ);
	}
	if (waitpid(-1, &status, 0) > 0) {
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
	}
	return 0;
}

int main(int ac, char **av, char **envp) {
	printf("%d\n", mysystem("ls"));
	printf("%d\n", mysystem("./exit-code"));
}