/* $begin cpfile */
#include "csapp.h"

int main(int argc, char **argv) 
{
	int n;
	rio_t rio;
	char buf[MAXBUF];

	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = Rio_readlineb(&rio, buf, MAXBUF)) != 0) {
		Rio_writen(STDOUT_FILENO, buf, n);
	}
	exit(0);
}
/* $end cpfile */


