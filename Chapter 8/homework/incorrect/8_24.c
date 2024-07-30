// psignal


/* $begin waitpid1 */
#include "csapp.h"
#define N 2

void handler(int sig) {
	psignal(SIGSEGV, NULL);
}

int main(int ac, char **av) 
{
	int status, i;
	pid_t pid;

	/* Parent creates N children */
	for (i = 0; i < N; i++)					   //line:ecf:waitpid1:for
		if ((pid = Fork()) == 0) { /* Child */	 //line:ecf:waitpid1:fork
			char* cptr = NULL;
			*cptr = 'd';
		}

	/* Parent reaps N children in no particular order */
	while ((pid = waitpid(-1, &status, 0)) > 0) { //line:ecf:waitpid1:waitpid
		if (WIFEXITED(status))					//line:ecf:waitpid1:wifexited
			printf("child %d terminated normally with exit status=%d\n",
				pid, WEXITSTATUS(status));	 //line:ecf:waitpid1:wexitstatus
		else if (WIFSIGNALED(status)) {
			char buf[100];
			sprintf(buf, "child %d terminated by signal %d", pid, WTERMSIG(status));
			psignal(WTERMSIG(status), buf);
		} else
      		printf("child %d terminated abnormally\n", pid);
			
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD)						  //line:ecf:waitpid1:errno
		unix_error("waitpid error");

	exit(0);
}
/* $end waitpid1 */