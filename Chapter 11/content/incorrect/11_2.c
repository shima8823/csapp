// hex2dd.c
// sscanfとin_addrの使いかた。
#include "csapp.h"

int main(int ac, char **av) {
	struct in_addr inaddr;
	u_int32_t addr;
	char buf[MAXBUF];

	if (ac != 2) {
		return 1;
	}
	sscanf(av[1], "%x", &addr);
	inaddr.s_addr = htonl(addr);
	
	if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF))
		unix_error("inet_ntop");
	printf("%s\n", buf);
}