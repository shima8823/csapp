#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

void cond(long a, long *p) {
	if (p == 0)
		goto l1;
	if (*p >= a)
		goto l1;
	*p = a;
l1:
	return;
}

// B. asm は&&を使えないため。

int main() {
	
	return 0;
}