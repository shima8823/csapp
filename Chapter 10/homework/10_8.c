/* $begin statcheck */
#include "csapp.h"

int main (int argc, char **argv) 
{
	struct stat stat;
	char *type, *readok;

	// Open("../homework", O_RDONLY, S_IRUSR);

	if (argc != 2) {
		fprintf(stderr, "usage: %s <file discpritor>\n", argv[0]);
		exit(0);
	}
	int fd = atoi(argv[1]);

	if (fd < 0) {
		fprintf(stderr, "invalid fd: %d\n", fd);
		exit(0);
	}
	Fstat(fd, &stat);
	if (S_ISREG(stat.st_mode))	 /* Determine file type */
		type = "regular";
	else if (S_ISDIR(stat.st_mode))
		type = "directory";
	else 
		type = "other";
	if ((stat.st_mode & S_IRUSR)) /* Check read access */
		readok = "yes";
	else
		readok = "no";

	printf("type: %s, read: %s\n", type, readok);
	exit(0);
}
/* $end statcheck */