#include <unistd.h>
#include <stdio.h>

unsigned int snooze(unsigned int secs) {
	unsigned int slept = sleep(secs) ;
	printf("Slept for %d of %u secs\n", slept, secs);
	return slept;
}

int main() {
	snooze(3);
}