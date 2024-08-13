#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

typedef unsigned packed_t;

// bytenum = 1
// 0001
// 0000 1000
// 8

// bytenum = 2
// 0010
// 0001 0000
// 16

// bytenum = 3
// 0100
// 0010 0000
// 32

// A 32ビットシフトしているから。

int xbyte(packed_t word, int bytenum) {
	return (word >> (bytenum * 8)) & 0xFF;
}

// A This function can’t extract negetive number from packet_t word.
int xbyte_correct(packed_t word, int bytenum) {
	int max_bytenum = 3;
  	return (int) word << ((max_bytenum - bytenum) << 3) >> (max_bytenum << 3);
}

int main() {
	assert(xbyte(0x00112233, 0) == 0x33);
	assert(xbyte(0x00112233, 1) == 0x22);
	assert(xbyte(0x00112233, 2) == 0x11);
	assert(xbyte(0x00112233, 3) == 0x00);

	assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
	assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
	assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
	assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);

	return 0;
}