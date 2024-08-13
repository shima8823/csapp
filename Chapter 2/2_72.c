#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef unsigned char *byte_pointer;

// sizeof() -> size_t
// unsigned size_t

// A. int型とunsigned型の演算はunsigned型にキャストされてしまうため、maxbytesが低くても負の数にはならない。

void copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes >= sizeof(val))
		memcpy(buf, (void *)&val, sizeof(val));
}

int main() {
	
	return 0;
}