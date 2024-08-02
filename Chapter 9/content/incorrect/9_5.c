//良問

/* $begin mmapcopy */
#include "csapp.h"

/* 
 * mmapcopy - uses mmap to copy file fd to stdout 
 */
void mmapcopy(int fd, int size) 
{
    char *bufp; /* ptr to memory-mapped VM area */

    bufp = Mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    Write(1, bufp, size);
    return;
}

/* mmapcopy driver */
int main(int argc, char **argv) 
{
    struct stat stat;
    int fd;

    /* Check for required command-line argument */
    if (argc != 2) {
	printf("usage: %s <filename>\n", argv[0]);
	exit(0);
    }

    /* Copy the input argument to stdout */
    fd = Open(argv[1], O_RDONLY, 0);
    fstat(fd, &stat);
    mmapcopy(fd, stat.st_size);
    exit(0);
}
/* $end mmapcopy */




// #include <unistd.h>
// #include <sys/mman.h>
// #include <fcntl.h>
// #include <stdlib.h>

// int main(int ac, char **av) {
// 	if (ac < 2)
// 		return 1;

// 	int fd = open(av[1], O_RDONLY);
// 	if (fd == -1) {
// 		exit(EXIT_FAILURE);
// 	}
	
// 	char buf[1000];

// 	read(fd, buf, 1000);
// 	mmap(buf, 1000, PROT_READ, MAP_PRIVATE, STDOUT_FILENO, 0);
// }


