#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// n bit分埋める

// n = 6, 0x3F
// 0000 0000 0000 0000 0000 0000 0011 1111

// n = 17, 0x1FFFF
// 0000 0000 0000 0001 1111 1111 1111 1111

int lower_one_mask(int n) {
	int x = -1;
	int w = sizeof(int) * 8;
	return ((unsigned) x >> (w - n));
}

int main() {
	printf("%x\n", lower_one_mask(6));
	printf("%x\n", lower_one_mask(17));
	return 0;
}