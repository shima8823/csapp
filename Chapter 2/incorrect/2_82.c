#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// A INT_MIN
int A(int x, int y) {
	return (x < y) == (-x > -y);
}

// B true (<< 4)は*16
int B(int x, int y) {
	return ((x + y) << 4) + y-x == 17*y+15*x;
}

// C ?
/*
 * right
 *
 * ~x + ~y + 1
 *   =>
 * ~x + 1 + ~y + 1 - 1
 *   =>
 * -x + -y - 1
 *   =>
 * -(x + y) - 1
 *   =>
 * ~(x + y) + 1 - 1
 *   =>
 * ~(x + y)
 */
int C(int x, int y) {
	return ~x + ~y + 1 == ~(x + y);
}

// D 結局はビット演算なので-(y - x) = x - yになる
int D(int x, int y) {
	unsigned ux = (unsigned) x;
	unsigned uy = (unsigned) y;
	return (ux - uy) == -(unsigned)(y-x);
}

// E true  
/*
 * right
 *
 * x >> 2 << 2
 *   =>
 * x & ~0x3
 *   =>
 * x - num(00/01/10/11)
 *   =>
 * ((x >> 2) << 2) <= x
 */
int E(int x, int y) {
	return ((x >> 2) << 2) <= x;
}


int main() {
	printf("%d\n", A(INT_MIN, 0));
	printf("%d\n", B(10, INT_MAX));
	printf("%d\n", C(INT_MIN, INT_MAX));
	printf("%d\n", D(INT_MIN, INT_MAX));	
	return 0;
}