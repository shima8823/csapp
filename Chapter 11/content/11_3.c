// dd2hex.c

#include "csapp.h"

int main(int argc, char const *argv[])
{
	struct in_addr inaddr;
	if (!inet_pton(AF_INET, argv[1], &inaddr))
		unix_error("inet_pton");
	inaddr.s_addr= ntohl(inaddr.s_addr);
	printf("0x%x\n", inaddr.s_addr);
	return 0;
}
