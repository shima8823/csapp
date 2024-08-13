#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// x/2^k
// x = 5 k = 0: 0101 >> 2

// x = 64 k = 4: x = 0100 0000 k = 0100
int divide_power2(int x, int k) {
	return x >> k;
}

int correct_divide_power2(int x, int k) {
  int is_neg = x & INT_MIN;
  (is_neg && (x = x + (1 << k) - 1));
  return x >> k;
}

int main() {
	int x = 0x80000007;
	// assert(divide_power2(5, 0) == 5);
	// assert(divide_power2(64,4) == 4);
	printf("%d\n", divide_power2(5,0));
	printf("%d\n", divide_power2(64,4));
	printf("%d\n", divide_power2(x, 1));
	printf("%d\n", x / 2);
	printf("%d\n", divide_power2(x, 2));
	printf("%d\n", x / 4);
	return 0;
}