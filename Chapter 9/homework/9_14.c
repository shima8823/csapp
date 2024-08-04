#include "csapp.h"
#include <assert.h>

void mmapcopy(int fd, int size) 
{
    char *bufp;

    bufp = Mmap(NULL, size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	*bufp = 'J';
    Write(fd, bufp, size);
	Munmap(bufp, size);
    return;
}

int main(int argc, char **argv) 
{
    struct stat stat;
    int fd;

    fd = Open("hello.txt", O_RDWR, 0);
    fstat(fd, &stat);
    mmapcopy(fd, stat.st_size);
    exit(0);
}


// Mmap MAP_SHAREDでもよし
