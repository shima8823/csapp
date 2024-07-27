#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int slept;

void sigint_handler(int sig)
{
	// printf("	Users hit Crtl+C after %d seconds!\n", slept);
	return;
}

unsigned int snooze(unsigned int secs) {
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(1);
	slept = sleep(secs) ;
	printf("Slept for %d of %u secs\n", secs - slept, secs);
	return slept;
}

int main(int argc, char *argv[], char *environ[]) {
	if (argc != 2)
		exit(1);
	snooze(atoi(argv[1]));

}