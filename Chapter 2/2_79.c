#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// 3 * x / 4
// 3 = 0011
// 3 * 1 = 0011
// 3 * 2 = 0110
//   0010
// 3 * 3 = 1001

// 3 = 2 * 0 + 2 * 1
//     1     + 2
int mul3div4(int x) {
	int is_neg = x & INT_MIN;
  	(is_neg && (x = x + 1));
	return ((((int16_t)x << 1) + x) >> 2);
}

int main() {
	printf("%d\n", mul3div4(3));
	printf("%d\n", mul3div4(0));
	printf("%d\n", mul3div4(-1));
	printf("%d\n", mul3div4(-3));
	printf("%d\n", mul3div4(-4));
	return 0;
}