#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

void good_echo() {
	char buf[10];
	
	while(fgets(buf, sizeof(buf), stdin)) {
		printf("%s", buf);
	}
}

int main() {
	good_echo();
}