#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// 0x12345678
// n = 4:  0x23456781
// n = 20: 0x67812345

unsigned rotate_left(unsigned x, int n) {
	int w = sizeof(int) * 8;
	int mask = ~((unsigned) -1 >> n);
	// n = 4: 1111 0000 .... 0000
	int left_save = x & mask;
	x = x << n;
	left_save = (unsigned) left_save >> (w - n);
	return x | left_save;
}

int main() {
	printf("%x\n", rotate_left(0x12345678, 4));
	printf("%x\n", rotate_left(0x12345678, 20));
	return 0;
}