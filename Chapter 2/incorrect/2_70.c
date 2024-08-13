#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// x = 17: 0001 0001

// n = 4 : 0
// n = 6 : 1

// return 1 when x can be represented as an n-bit, 2's complement number
int fits_bits(int x, int n) {
	int w = sizeof(int) << 3;
	int offset = w - n;
	// assert(!fits_bits(0xFF, 8));
	// offset = 24
	// 0000 0000 0000 0000 0000 0000 1111 1111 << 24
	// 1111 1111 0000 0000 0000 0000 >> 24
	// 1111 1111 .... 1111 1111

	// x = 0b0010, n = 3
	// 0000 0000 0000 0000 0000 0000 0000 0010 << 29
	// 0100 0000 0000 0000 0000 0000 0000 0000 >> 29
	return (x << offset >> offset) == x;
}



int main() {
	assert(!fits_bits(0xFF, 8));
	// 1111 1111, n = 8
	assert(!fits_bits(~0xFF, 8));

	assert(fits_bits(0b0010, 3));
	0b11111111;
	0b11111111111111111111111100000000;
	return 0;
}