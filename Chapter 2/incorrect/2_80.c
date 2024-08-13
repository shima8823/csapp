#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// x = -9
// 1111 ... 1111 0111
// 
int threefourths(int x) {
  int is_neg = x & INT_MIN;
  int f = x & ~0x3;
  int l = x & 0x3;

  int fd4 = f >> 2;
  int fd4m3 = (fd4 << 1) + fd4;

  int lm3 = (l << 1) + l;
  int bias = (1 << 2) - 1;
  (is_neg && (lm3 += bias));
  int lm3d4 = lm3 >> 2;

  return fd4m3 + lm3d4;
}



int main() {
	printf("%d\n", (int)((int64_t)INT_MIN * 3 / 4));

	printf("%d\n", threefourths(INT_MIN));
	printf("%d\n", threefourths(-4));
	printf("%d\n", threefourths(0));
	printf("%d\n", threefourths(4));
	printf("%d\n", threefourths(INT_MAX));

	printf("%d\n", threefourths(8) == 6);
	printf("%d\n", threefourths(9) == 6);
	printf("%d\n", threefourths(10) == 7);
	printf("%d\n", threefourths(11) == 8);
	printf("%d\n", threefourths(12) == 9);

	printf("%d\n", threefourths(-8) == -6);

	printf("%d\n", threefourths(-9) == -6);
	printf("%d\n", threefourths(-10) == -7);
	printf("%d\n", threefourths(-11) == -8);

	printf("%d\n", threefourths(-12) == -9);

	printf("fail %d\n", threefourths(-9));
	printf("%d\n", threefourths(-10));
	printf("%d\n", threefourths(-11));
	return 0;
}